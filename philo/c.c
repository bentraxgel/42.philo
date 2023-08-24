#include "philo.h"

int	pick_up_fork(t_philo *philo, int flag)
{
	while (true)
	{
		if (monitoring(philo) == DEAD)
			return (DEAD);
		pthread_mutex_lock(&philo->fork[flag]->mutex);
		if (philo->fork[flag]->status == UNLOCK)
		{
			philo->fork[flag]->status = LOCK;
			print_shell(philo, "has taken a fork");
			pthread_mutex_unlock(&philo->fork[flag]->mutex);
			return (LIVE);
		}
		pthread_mutex_unlock(&philo->fork[flag]->mutex);
		// usleep(200);
	}
}

void	put_down_fork(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->fork[flag]->mutex);
	philo->fork[flag]->status = UNLOCK;
	pthread_mutex_unlock(&philo->fork[flag]->mutex);
}


int	dining(t_philo *philo)
{
	if (pick_up_fork(philo, LEFT) == DEAD)
		return (DEAD);
	if (pick_up_fork(philo, RIGHT) == DEAD)
		return (DEAD);
	eating(philo);
	put_down_fork(philo, LEFT);
	put_down_fork(philo, RIGHT);
	return (LIVE);
}