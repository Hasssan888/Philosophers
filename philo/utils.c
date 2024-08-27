#include "philo.h"

int     is_died(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->mutex_is_dead);
    if (philo->data->is_die)
    {
        pthread_mutex_unlock(&philo->data->mutex_is_dead);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->mutex_is_dead);
    return (0);
}

int     full(t_philo* philo)
{
    if (philo->data->meals_nb > 0 && philo->meals_eat >= philo->data->meals_nb)
    {
        pthread_mutex_lock(&philo->data->mutex_flag_eat);
        if ((philo->data->meals_nb * philo->data->philo_nb) == philo->data->flag_eat)
        {
            pthread_mutex_unlock(&philo->data->mutex_flag_eat);
            pthread_mutex_lock(&philo->data->mutex_full);
            philo->data->is_full = 1;
            pthread_mutex_unlock(&philo->data->mutex_full);
            return (0);
        }
        pthread_mutex_unlock(&philo->data->mutex_flag_eat);
        return (0);
    }
    return (1);
}
