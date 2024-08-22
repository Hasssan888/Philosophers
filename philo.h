# ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo
{
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long    last_meal_time;
    int id;
    struct s_data *data;
} t_philo;

typedef struct s_data
{
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long meals_nb;
    long philo_nb;

    int is_die;
    int is_full;
    pthread_mutex_t write;
    pthread_mutex_t m_eat;
    pthread_mutex_t *forks;
    pthread_t *philosophers;
    t_philo *philo;
    long    start;

} t_data;

int	    ft_isdigit(int d);
long	ft_atoi(const char *str);


# endif