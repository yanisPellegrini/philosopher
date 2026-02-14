# Philosophers

*This project has been created as part of the 42 curriculum by ypellegr.*

## Description

Philosophers is a multithreading project that simulates the classic dining philosophers problem. Each philosopher is represented by a thread and must eat, sleep, and think while avoiding starvation and deadlock.

The goal is to understand:
- Thread creation and synchronization
- Mutex usage to protect shared resources
- Race condition prevention
- Deadlock avoidance

## Instructions

### Compilation

```bash
make
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in ms before a philosopher dies without eating
- `time_to_eat`: Time in ms for a philosopher to eat
- `time_to_sleep`: Time in ms for a philosopher to sleep
- `[number_of_times_each_philosopher_must_eat]`: (Optional) Stops when all philosophers have eaten this many times

### Examples

```bash
# 5 philosophers, no one should die
./philo 5 800 200 200

# Stops after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# 1 philosopher (should die - cannot eat with only 1 fork)
./philo 1 800 200 200
```

### Cleaning

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile everything
```

## Resources

### Documentation
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_create man page](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [pthread_mutex man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)

### AI Usage
AI (Claude) was used to:
- Explain threading concepts and mutex usage
- Help structure the code architecture
- Debug race conditions and deadlock issues

All AI-generated code was reviewed, tested, and understood before integration.

## Project Structure

```
philo/
├── Makefile
├── README.md
├── includes/
│   └── philo.h
└── srcs/
    ├── main.c
    ├── init.c
    ├── uti.c
    ├── actions.c
    ├── routine.c
    ├── monitor.c
    └── cleanup.c
```

## Key Features

- **Anti-deadlock mechanism**: Philosophers with even IDs take forks in reverse order
- **Thread-safe operations**: All shared data protected by mutexes
- **Precise timing**: Custom `ft_usleep()` for accurate time delays
- **Death detection**: Monitor thread checks every 0.5ms to detect death within 10ms
- **No data races**: Verified with Valgrind's helgrind tool
- **No memory leaks**: All allocated memory properly freed
