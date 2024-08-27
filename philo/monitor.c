#include "philo.h"


void    *monitor(void *args)
{
    t_data *data;
    int i;

    data = (t_data *)args;
    data->full_philos = 0;
    usleep(100);
    while (1)
    {
        i = 0; 
        while(i < data->philo_nb)
        {
            pthread_mutex_lock(&data->mutex_full);
            pthread_mutex_lock(&data->mutex_flag_eat);
            if (data->meals_nb > 0 && data->philo[i].meals_eat >= data->meals_nb)
            {
                data->full_philos++;
                if (data->full_philos == data->philo_nb)
                {
                    data->is_full = 1;
                    pthread_mutex_unlock(&data->mutex_full);
                    pthread_mutex_unlock(&data->mutex_flag_eat);
                    return (NULL);
                }
            }
            pthread_mutex_unlock(&data->mutex_full);
            pthread_mutex_unlock(&data->mutex_flag_eat);

            pthread_mutex_lock(&data->philo[i].last_meal_time);
            if (get_time() - data->philo[i].last_meal_time > data->time_to_die && data->philo[i].is_eating == 0)
            {
                pthread_mutex_unlock(&data->philo[i].last_meal_time);
                pthread_mutex_lock(&data->mutex_is_dead);
                data->is_die = 1;
                pthread_mutex_unlock(&data->mutex_is_dead);
                printf("%ld %d died\n", get_time() - data->start, data->philo[i].id);
                return (NULL);
            }
            pthread_mutex_unlock(&data->philo[i].last_meal_time);
            usleep(100);
            i++;
        }
    }
}
