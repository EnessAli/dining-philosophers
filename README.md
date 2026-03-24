# Dining Philosophers

A concurrent simulation of Dijkstra's classic **Dining Philosophers Problem**, implementing both **mutex-based** (threads) and **semaphore-based** (processes) solutions to prevent deadlock and starvation.

## Problem Statement

*N philosophers* sit at a round table. Each philosopher alternates between **thinking**, **picking up forks**, **eating**, and **putting down forks**. Each philosopher needs two forks (shared with neighbors) to eat. The challenge: prevent deadlock and ensure no philosopher starves.

## Synchronization Strategies

### Mutex Version (threads)
- One `pthread_mutex_t` per fork
- Philosophers are `pthread_t` threads sharing memory
- A dedicated monitor thread checks death conditions
- Odd/even stagger to reduce contention

### Semaphore Version (processes)
- Philosophers are `fork()`ed processes
- A global semaphore controls total concurrent eaters
- Per-philosopher semaphores protect death reporting

## Deadlock Prevention

- **Asymmetric pickup**: even-indexed philosophers pick left fork first; odd-indexed pick right first
- **N-1 rule**: at most N-1 philosophers can attempt eating simultaneously
- **Timestamp precision**: `gettimeofday` at microsecond resolution ensures accurate starvation detection

## Build & Run

```bash
make

# 5 philosophers, die after 800ms, eat for 200ms, sleep 200ms
./philo 5 800 200 200

# with optional meal count (each must eat at least 7 times)
./philo 5 800 200 200 7
```

### Output Format
```
timestamp_ms philosopher_id action
0           1            is thinking
10          2            has taken a fork
10          2            is eating
210         2            is sleeping
...
```

## Tech Stack

`C` `pthreads` `Mutex` `Semaphore` `Fork` `Concurrency` `POSIX`

