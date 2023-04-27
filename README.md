<h1 align="center">🍽️ philosophers</h1>

<p align="center">
	<b><i>Philosophers is a 42 school project that consists in creating a program that reproduce the dining philosophers problem.</i></b><br>
</p>

<p align="center">
	<img alt="Top used language" src="https://img.shields.io/github/languages/top/okbrandon/philosophers?color=success"/>
	<img alt="Norminette run" src="https://github.com/okbrandon/philosophers/actions/workflows/42-norminette.yml/badge.svg"/>
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/okbrandon/philosophers"/>
</p>

## 📚 Table of Contents

- [👨‍🏫 Demonstration](#-demonstration)
- [📚 Table of Contents](#-table-of-contents)
- [📦 Installation](#-installation)
- [📝 Usage](#-usage)
- [📝 Example](#-example)

## 👨‍🏫 Demonstration

https://user-images.githubusercontent.com/103316367/234917126-de4c1755-0030-417e-8915-7237a5b5edc6.mov

> Running simulation with 5 philosophers. `./philo 5 800 200 200` 

## 📦 Installation

Clone the repository from GitHub:
```sh
git clone https://github.com/okbrandon/philosophers.git
```

Compile the `philo` executable:
```sh
cd philo/ && make
```

Compile the `philo_bonus` executable:
```sh
cd philo_bonus/ && make
```

## 📝 Usage

Run the mandatory program:
```sh
./philo <num_of_philo> <time_to_die> <time_to_eat> <time_to_sleep> [<must_eat>]
```
> First parameter is how much philosophers you want, the second one is after how many millis they should die after their last meal, the third one is the time they take to eat in millis, same for the forth parameter. The last one is optional and represent how many times each philosopher should eat at least.

Run the bonus program:
```sh
./philo_bonus <num_of_philo> <time_to_die> <time_to_eat> <time_to_sleep> [<must_eat>]
```
> Same as above.

## 📝 Example

Valid simulation:
```sh
$> ./philo 5 800 200 200
0           1 has taken a fork
0           3 has taken a fork
0           3 has taken a fork
0           3 is eating
0           1 has taken a fork
0           1 is eating
0           5 has taken a fork
200         4 has taken a fork
200         3 is sleeping
200         5 has taken a fork
200         5 is eating
200         1 is sleeping
200         2 has taken a fork
200         2 has taken a fork
200         2 is eating
[...]
```

Invalid simulation:
```sh
$> ./philo 5 400 200 200
0           1 has taken a fork
0           1 has taken a fork
0           1 is eating
0           3 has taken a fork
0           3 has taken a fork
0           5 has taken a fork
0           3 is eating
200         3 is sleeping
200         5 has taken a fork
200         5 is eating
200         1 is sleeping
200         4 has taken a fork
200         2 has taken a fork
200         2 has taken a fork
200         2 is eating
400         3 is thinking
400         3 has taken a fork
400         2 is sleeping
400         5 is sleeping
400         1 is thinking
400         1 has taken a fork
400         4 has taken a fork
400         4 is eating
400         1 died
```

> The bonus program has the same output as the mandatory one. The only difference is that the mandatory uses mutexes and the bonus one semaphores.

[⬆ Back to Top](#-table-of-contents)

## 🌏 Meta

bsoubaig – bsoubaig@student.42nice.fr
