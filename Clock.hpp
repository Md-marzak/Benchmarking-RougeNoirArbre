#ifndef CLOCK_HPP_INCLUDED
#define CLOCK_HPP_INCLUDED
#include <chrono>
#include <string>
#include <sstream>

class Clock
{
    private :
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
    public :
        void chronoStart(void)
        {
            this->start = std::chrono::high_resolution_clock::now();
        }
        void chronoEnd(void)
        {
            this->end = std::chrono::high_resolution_clock::now();
        }

        const double milliseconds() const
        {
            return std::chrono::duration<double, std::milli>(end - start).count();
        }

        const double microseconds() const
        {
            return std::chrono::duration<double, std::micro>(end - start).count();
        }

        const double seconds() const
        {
            return std::chrono::duration<double>(end - start).count();
        }

        std::string display(char *monMsg, int unite = 2) const
        {
            std::ostringstream out;  // String Builder

            switch (unite) {
                case 1: {
                    out << monMsg << this->seconds() << " seconds";
                    break;
                }

                case 3: {
                    out << monMsg << this->microseconds() << " microseconds";
                    break;
                }

                default: {
                    out << monMsg << this->milliseconds() << " milliseconds";
                    break;
                }
            }

            return ("\n" + out.str());  // Return The Full String
        }
};


#endif // CLOCK_HPP_INCLUDED
