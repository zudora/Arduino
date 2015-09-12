using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace PWMtest
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
             Fade

             This example shows how to fade an LED on pin 9
             using the analogWrite() function.

             This example code is in the public domain.
             */       
            //loop through duty cycles
            //duty is percentage of time pin is high
            //effective per-cycle high time is full_cycle/duty
            //reps are the number of cycles to run it

            //number of milliseconds in a full on-off cycle
            float full_cycle = 3;
            int num_reps = 100;

            for (int duty = 0; duty <= 100; duty++)
            {
                for (int reps_done = 0; reps_done < num_reps; reps_done++)
                {
                    float high_time = full_cycle * duty / 100;
                    Debug.WriteLine("HIGH: " + high_time + ", duty: " + duty + ", percentage: " + high_time/full_cycle);
                    float high_delay = high_time;
                    //Console.WriteLine("LOW: " + led);
                    float low_delay = full_cycle - high_time;
                }
            }
        }
    }
}
