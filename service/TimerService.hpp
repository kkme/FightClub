#ifndef __TIMERSERVICE_H
#define __TIMERSERVICE_H

namespace PWRD{

	namespace MoM{

		class TimerService: public Service{

			public:
				void Run();


			protected:

				virtual int init();

				virtual int fini();

			private:

		};
		

	}

}

#endif
