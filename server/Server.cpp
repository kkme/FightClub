#include <Server.hpp>
namespace PWRD{

	namespace Network{

		//===================================================================
		// Server
		//===================================================================
		/*
		   @protected
		 */
		int Server::init(){

			acceptor_ = new Acceptor(addr_);

			if(NULL == acceptor_){

				Error("New Acceptor Error");

				return -1;

			}

			return 1;

		}

		int Server::fini(){

			delete acceptor_;

			acceptor_ = NULL;

			return 1;

		}


		/*
		   @public
		   */
		void Server::Open(){

			Trace("TRACE Open Acceptor Handler");

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);
		}

		Handle Server::GetHandle() const{

			return acceptor_->GetHandle();

		}

		int Server::Receive(){

			Session *sh_ = new Session();

			Trace("TRACE New Session: addr=%p", sh_);

			if(NULL == sh_){

				Error("New Session failed");
				return -1;

			}

			acceptor_->Accept(sh_->GetStream());

			sh_->Open(timeout_);

			Note("Accept a client: handle=%d", sh_->GetHandle());

			return 0;
		}
	};

}
