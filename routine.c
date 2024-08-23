#include "philo.h"

void    print_msg(char *msg, t_philo *philo)
{
    pthread_mutex_lock(&philo->data->mutex_write);
    pthread_mutex_lock(&philo->data->mutex_is_dead);
    if (philo->data->is_die)
    {
        pthread_mutex_unlock(&philo->data->mutex_write);
        pthread_mutex_unlock(&philo->data->mutex_is_dead);
        return ;
    }
    pthread_mutex_unlock(&philo->data->mutex_write);
    pthread_mutex_unlock(&philo->data->mutex_is_dead);
    pthread_mutex_lock(&philo->data->mutex_full);
    if (philo->data->is_full)
    {
        pthread_mutex_unlock(&philo->data->mutex_full);
        return ;
    }
    pthread_mutex_unlock(&philo->data->mutex_full);
    pthread_mutex_lock(&philo->data->mutex_write);
    printf("%ld %d %s", get_time() - philo->data->start, philo->id, msg);
    pthread_mutex_unlock(&philo->data->mutex_write);

}
void    eating(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_msg("take a fork\n", philo);
    pthread_mutex_lock(philo->right_fork);
    print_msg("take a fork\n", philo);
    print_msg("is eating\n",philo);
    ft_usleep(philo->data, philo->data->time_to_eat);
    pthread_mutex_lock(&philo->data->mutex_flag_eat);
    philo->data->meals_nb++;
    pthread_mutex_unlock(&philo->data->mutex_flag_eat);
    pthread_mutex_lock(&philo->data->last_meal_eat);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->data->last_meal_eat);
    philo->meals_eat++;
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

int     sleeping(t_philo *philo)
{
    if (is_died(philo) == 1)
        return (0);
    if (!full(philo))
        return (0);
    print_msg("is thinking\n", philo);
    ft_usleep(philo->data, philo->data->time_to_sleep);
    if (is_died(philo))
        return (1);
    print_msg("is thinking\n", philo);
    return (1);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;

    if(philo->id % 2 == 0)
        usleep(200);

    while(1)
    {
        eating(philo);
        if (!sleeping(philo))
            break;
        if (philo->data->philo_nb < 20)
            usleep(500);
    }
    return (NULL);
}