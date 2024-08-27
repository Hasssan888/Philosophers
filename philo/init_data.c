#include "philo.h"

int init_mutex(t_data *data)
{
    pthread_mutex_init(&data->last_meal_eat , NULL);
    pthread_mutex_init(&data->mutex_full , NULL);
    pthread_mutex_init(&data->mutex_is_dead , NULL);
    pthread_mutex_init(&data->mutex_flag_eat , NULL);
    pthread_mutex_init(&data->mutex_write , NULL);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
    if (!data->forks)
        return (1);
    int i = -1;
    while(++i < data->philo_nb)
        pthread_mutex_init(&data->forks[i], NULL);
    return (0);
}
int assign_forks(t_data *data)
{
    int i = -1;
    while(++i < data->philo_nb)
    {
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].right_fork = &data->forks[(i + 1) % data->philo_nb];
        if (data->philo[i].id % 2 == 0)
        {
            data->philo[i].left_fork = &data->forks[(i + 1) % data->philo_nb];
            data->philo[i].right_fork = &data->forks[i];
        }
    }
    return 0;
}

int init_each_philo(t_data *data)
{
    int i = -1;
    data->philosophers = malloc(sizeof(pthread_t) * data->philo_nb);
    while(++i < data->philo_nb)
    {
        data->philo[i].id = i + 1;
        data->philo[i].last_meal_time = get_time();
        data->philo[i].data = data;
        data->philo[i].meals_eat = 0;
        data->is_full = 0;
        data->is_die = 0;
        data->flag_eat = 0;

    }
    assign_forks(data);
    return 0;
}
