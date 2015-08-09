#include "EventPipeHandler.hpp"

namespace PWRD{

	namespace Event{

		/*
		 * @protected
		 */
		int EventPipeHandler::init(){

			pipe_ = new Pipe();

			assert(NULL != pipe_);

			*buf_ = 0;

			return 1;

		}



		int EventPipeHandler::fini(){

			if(NULL != pipe_){
				
				delete pipe_;

				pipe_ = NULL;

			}

			return 1;

		}

		/*
		 * @public
		 */

		int EventPipeHandler::Open(){


			//If the shell is running
			if(-1 != pid_){

				//Close fd
				close(pipe_->infd());

				//Kill the pid unless it exists
				if(PidSet::Exist(pid_)){

					Note("Kill the Process which not exist normal: pid=%d, shell=%s", pid_, shell_.c_str());

					PidSet::Kill(pid_);


				}

			}
			
			Note("Registe EventPipeHandler: handler=%p", this);

			Registry::RegisteHandler(this, shell_);

			Registry::RegisteRuntime(shell_, this);

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

			TimerQueue::Register(this, timeout_);

			return 1;

		}

		void EventPipeHandler::Start(){

			Execute();

		}

		int EventPipeHandler::Receive(){

			while(true){

				int len = read(pipe_->infd(), buf_, BUFSIZ);

				if(-1 == len){

					if(EAGAIN == errno){

						break;

					}

					else if(EINTR == errno){

						continue;

					}

					else{

						Error("Close the fd:%d", pipe_->infd());

						return -1;

					}

				}

				buf_[len] = 0;

				strbuf_.assign(buf_);

				Return();

				if(len < BUFSIZ){

					Error("Read %d bytes from fd:%d", len, pipe_->infd());

					return len;

				}

			}

			return 0;

		}



		int EventPipeHandler::Send(){

			return 1;

		}


		int EventPipeHandler::Timeout(bool& _flag UNUSED){

			return Execute();

		}

		int EventPipeHandler::Execute(){

			pid_t pid = fork();

			if(pid < 0){

				Error("Fork error: errno=%d, errmsg=%s", errno, strerror(errno));

				return -1;

			}

			else if(pid == 0){

				//Child process
				pid_ = pid;

				//Change director to the path where the script stored
				chdir(path_.c_str());

				char *params[ARGC];

				getCMD(params);

				sigset_t set;

				sigfillset(&set);

				sigprocmask(SIG_UNBLOCK, &set, NULL);

				close(pipe_->infd());

				close(STDIN_FILENO);

				dup2(pipe_->outfd(), STDOUT_FILENO);

				execvp(params[0], params);

				//exit(0);

			}

			close(pipe_->outfd());

			return 1;

		}

		int EventPipeHandler::Close(){

			Registry::RemoveHandler(this);

			Registry::RemoveRuntime(shell_);

			ReactorService::Instance()->Remove(this);

			TimerQueue::Remove(this);

			close(pipe_->outfd());

			if(PidSet::Exist(pid_)){

				PidSet::Kill(pid_);
				
			}

			delete this;

			return 1;

		}

		void EventPipeHandler::getCMD(char ** params){

			typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

			boost::char_separator<char> sep(" ");

			tokenizer tokens(shell_, sep);

			int step = 0;

			for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); tok_iter++){

				params[step] = new char[(*tok_iter).size()+1];

				strncpy(params[step], (*tok_iter).c_str(), (*tok_iter).size());

				params[step][(*tok_iter).size()] = 0;

				step++;

			}   

			params[step] = NULL;

		}



		int EventPipeHandler::Return(){

			Result* result = new Result();

			assert(result != NULL);

			result->set_type(type_);

			/*result->set_server(server_);*/

			result->set_sql(strbuf_);

			Registry::syncq()->Enqueue(result);

			Note("Send %d bytes: strbuf_=%s", strbuf_.size(), strbuf_.c_str());

			strbuf_ = "";

			return strbuf_.size();

		}//Return

	}//Event

}//PWRD

