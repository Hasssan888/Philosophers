#include "philo.h"

void    *monitor_2(t_data *data, int i, unsigned int tim_last_meal)
{
    pthread_mutex_lock(&data->mutex_full);
    if (data->is_full)
    {
        pthread_mutex_unlock(&data->mutex_full);
        return (NULL);
    }
    pthread_mutex_unlock(&data->mutex_full);
    if (tim_last_meal > data->time_to_die)
    {
        pthread_mutex_lock(&data->mutex_is_dead);
        data->is_die = 1;
        pthread_mutex_unlock(&data->mutex_is_dead);
        printf("%ld %d died\n", get_time() - data->start, data->philo[i].id);
        return (NULL);
    }
    return ((void *)1);
}

void    *monitor(void *args)
{
    t_data *data;
    int i;
    unsigned int tim_last_meal;
    void    *r;

    data = (t_data *)args;
    while (1)
    {
        i = 0;
        while (i < data->philo_nb)
        {
            pthread_mutex_lock(&data->last_meal_eat);
            tim_last_meal = get_time() - data->philo[i].last_meal_time;
            pthread_mutex_unlock(&data->last_meal_eat);
            r = monitor_2(data, i, tim_last_meal);
            if (r != (void *)1)
                return (r);
            i++;
            usleep(1000);
        }
        

    }
}