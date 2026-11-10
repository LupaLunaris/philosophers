# Philosophers

A concurrency exercise from the 42 curriculum, written in C with POSIX threads.

It models the dining philosophers problem: several threads share limited resources while each philosopher alternates between eating, sleeping and thinking.

## Build and run

```bash
make
./philo 5 800 200 200
```

Arguments: number of philosophers, time to die (ms), time to eat (ms), time to sleep (ms), and an optional number of meals.

```bash
./philo 5 800 200 200 7
```

## Implementation

- `init.c`: setup and argument handling
- `routine.c`: philosopher behaviour
- `monitor.c`: monitoring and termination
- `utils.c`: helpers and timing
- `main.c`: entry point

The Makefile currently enables ThreadSanitizer. This is useful for investigating concurrency problems, although it can affect timing.

## What I learned

The difficult part was coordinating shared state without introducing data races or deadlocks, while keeping timing behaviour understandable. This is a learning implementation.
