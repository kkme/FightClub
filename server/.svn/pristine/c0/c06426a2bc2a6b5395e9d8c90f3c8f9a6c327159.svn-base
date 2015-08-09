#include <TimerQueue.hpp>

namespace PWRD{

	namespace Event{

		TimeQ TimerQueue::timeq_;

		int TimerQueue::threshold_ = DEFAULTTIMER;

		TimerQueue *TimerQueue::instance_ = NULL;

		TimerQueue* TimerQueue::Instance(){

			Trace("TRACE TimerQueue Instance");

			if(NULL == instance_){

				Trace("TRACE New Instance of TimerQueue");

				instance_ = new TimerQueue();

			}

			return instance_;

		}

		void TimerQueue::Register(EventHandler* _handler, int _intra){

			if(NULL == _handler){

				Error("Illegal Handle: handler=%p", _handler);

				return;

			}

			if(_intra <= 0){

				Error("TRACE timer interval illegal: intra=%d", _intra);

				_intra = DEFAULTTIMER;

			}

			/*
			Trace("TRACE Register TimeQ: handler=%p, _intra=%d",
					_handler, _intra);
			*/

			timeq_[_handler] = _intra;

			Note("Registe a Handler: handler=%p, sum=%d",
					_handler, timeq_.size());

		}

		void TimerQueue::Remove(EventHandler* _handler){

			if(NULL == _handler){

				Error("Illegal Handle: handler=%p", _handler);

				return;

			}

			Trace("TRACE Remove the Handler: handler=%p", _handler);

			if(timeq_.find(_handler) != timeq_.end()){

				timeq_.erase(_handler);

				Note("Remove the Handler: handler=%p, sum=%d", _handler, timeq_.size());

			}


		}

		void TimerQueue::Set(int _threshold){

			if(_threshold < 0){

				Trace("TRACE Threshold less then 0: threshold=%d", _threshold);

				threshold_ = DEFAULTTIMER;

			}

			threshold_ = _threshold;

		}

		void TimerQueue::Start(void){

			Trace("TRACE TimerQueue Start");

		}

	}

}
