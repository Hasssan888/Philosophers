# include "philo.h"
int check_args(int ac, char **av)
{
    int i;
    int j;

    if (ac < 5 || ac > 6)
    {
        write(2, "error argument\n", 16);
        return (1);
    }
    i = 1;
    while (av[i])
    {
        j = 0;
        while(av[i][j])
        {
            if (!(av[i][j] >= '0' && av[i][j] <= '9'))
            {
                write(2, "error: you must be \n", 16);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}


int init_mutex(t_data *data)
{
    // pthread_mutex_init(&data->write, NULL);
    // pthread_mutex_init(&data->m_eat, NULL);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
    if (!data->forks)
        ;
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

    }
    assign_forks(data);
    return 0;
}


int init_philo(int ac, char **av, t_data *data)
{
    (void) ac;
    data->philo_nb = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->meals_nb = ft_atoi(av[5]);
    else 
        data->meals_nb = -1;
    data->philo = (t_philo *) malloc(sizeof(t_philo) * data->philo_nb);
    if (!data->philo)
    {
        write(2, "error: init data\n", 18);
        return (2);
    }
    init_mutex(data);
    init_each_philo(data);
    return 0;
}

// void take_froks(t_philo *philo)
// {
//     pthread_mutex_lock(philo->left_fork);
//     printf("%ld %d take a fork\n", get_time(), philo->id);
//     pthread_mutex_lock(philo->right_fork);
//     printf("%ld %d take a fork\n", get_time(), philo->id);

// }

// void philo_eat(t_philo *philo)
// {
//     printf("%ld %d is eating\n", get_time(), philo->id);
//     pthread_mutex_unlock(philo->right_fork);
//     pthread_mutex_unlock(philo->left_fork);

// }

// void    philo_sleep(t_philo *philo)
// {
//     pthread_mutex_lock(&(philo->data->write));
//     printf("%ld %d is sleeping\n", get_time(), philo->id);
//     pthread_mutex_unlock(&(philo->data->write));
//     ft_usleep(philo->data->time_to_sleep);
//     pthread_mutex_lock(&(philo->data->write));
//     printf("%ld %d is thinking\n", get_time(), philo->id);
//     pthread_mutex_unlock(&(philo->data->write));
// }

void *routine(void *arg)
{
    t_philo *philo = (t_philo *) arg;

    if(philo->id % 2 == 0)
        usleep(200);
    while(1)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d take a fork\n", get_time() - philo->data->start, philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d take a fork\n",get_time() - philo->data->start , philo->id);

        printf("%ld %d is eating\n",get_time() - philo->data->start , philo->id);
        ft_usleep(philo->data->time_to_eat);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        

        printf("%ld %d is sleeping\n",get_time() - philo->data->start , philo->id);
        ft_usleep(philo->data->time_to_sleep);
        printf("%ld %d is thinking\n",get_time() - philo->data->start , philo->id);


        // take_froks(philo);
        // philo_eat(philo);
        // philo_sleep(philo);
    }
}


int start_simuation(t_data *data)
{
    int i = -1;
    data->start = get_time();
    printf("%ld\n",data->start);
    while (++i < data->philo_nb)
        pthread_create(&data->philosophers[i], NULL, routine, &data->philo[i]);
    // monitor(data); // check if philo die
    i = -1;
    while (++i < data->philo_nb)
        pthread_join(data->philosophers[i], NULL);
    return 0;
}

int main(int ac, char **av)
{
    t_data data;
    if (check_args(ac, av))
        return (1);
    if (init_philo(ac, av, &data))
        return (1);
    if (start_simuation(&data))
        return (1);
    return (0);
}