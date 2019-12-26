//TODO mettre header

#include "ft_printf.h"



static double expo(int d, int exp)
{
    double result;

    result = 1;
    while (exp > 1)
    {
        result *= d;
        exp--;
    }
    return (result);
}

static int     first_char(long double nb)
{
    int result;

    result = 0;
    while (nb >= 10)
    {
        nb /= 10;
        result = nb;
    }
    return (result);
}

static long    nb_fdigit(double nb)
{
    long result;

    result = 0;
    if (nb < 10 && nb > -10)
        return (1);
    while (nb >= 1)
    {
        nb /= 10;
        result++;
    }
    return (result);
}

void	ft_putdbl_fd(double n, int fd, int i)
{
    int nb;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 10)
		ft_putdbl_fd((n / 10), fd, i);
    while (n >= 10000000)
    {
        nb = nb_fdigit(n);
        n -= (expo(10, nb) * first_char(n));
    }
    ft_putchar_fd(((int)n % 10) + '0', fd);
}

void    disp_float(t_pf* tpf)
{
    double val;
    double dup;
    int argsize;
    int cmp;

    cmp = 0;
    argsize = 0;
	val = va_arg(*(tpf->ap), double);
    if (val < 0)
    {
        ft_putchar_fd('-', 1);
        val *= -1;
    }
    dup = val;
    //obtenir argsize
    argsize = nb_fdigit(dup);
    //obtenir nb_whitespace
    (!tpf->fprecision) ? tpf->vprecision = 6 : 0;
        tpf->width > argsize + tpf->vprecision ? tpf->whitespace = tpf->width - (argsize + tpf->vprecision + 1) : 0;
    ft_putcharec_fd(' ', tpf->whitespace, 1);
    ft_putdbl_fd(val, 1, 0);
    //afficher les chiffres apres la virgulefg
    (tpf->vprecision == 0) ? 0 :ft_putchar_fd('.', 1);
    dup = val;

    int nb;
    int x = 0;
    dup += 0.5 / expo(10, tpf->vprecision + 1);
    while (dup >= 10)
    {
        nb = nb_fdigit(dup);
        dup -= (expo(10, nb) * first_char(dup));
    }
    while (cmp < tpf->vprecision)
    {
        dup *= 10;
        ft_putnbr_fd(((int)dup) % 10, 1);
        cmp++;
        nb = nb_fdigit(dup);
        x = first_char(dup);
        if (nb)
            dup -= (expo(10, nb) * x);    
    }
    tpf->length += tpf->whitespace;
    tpf->length += argsize;
    tpf->length += tpf->vprecision;
    (val >= 0) ? tpf->length++ : (tpf->length += 2);
}