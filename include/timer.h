#ifndef TIMER_H
#define TIMER_H

namespace Eternal {
    class Timer {
        public:
            Timer();
            ~Timer();

            int GetTicks();
            void Start();
            void Stop();
            bool Ticking();
        private:
            int iTicks;
            bool bTicking;
    };
}

#endif
