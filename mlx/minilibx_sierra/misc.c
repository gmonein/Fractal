#include "fdf.h"

int		ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	if (c <= a && c <= b)
		return (c);
	return (0);
}

int		ft_max(int a, int b, int c)
{
	if (a >= b && a >= c)
		return (a);
	if (b >= a && b >= c)
		return (b);
	if (c >= a && c >= b)
		return (c);
	return (0);
}

unsigned	find_color(t_p *p, t_coord a)
{
	unsigned		color;
	char			*rgb;
	char			ratio;
	char			cc;

	rgb = (char *)&color;
	color = 0xFFFFFFFF;
	if (a.dy == 0)
		a.dy = 1;
	if (a.dx == 0)
		a.dx = 1;
	if (a.dx < a.dy)
		cc = ((a.dy * 128000) / a.dx) / 1000;
	else
		cc = ((a.dx * 128000) / a.dy) / 1000;
	color |= 0xFF000000;
	if (cc < 0)
		cc *= -1;
	cc += 127;
	rgb[0] = cc;
	rgb[1] = cc;
	rgb[2] = cc;
	color &= p->color;
	return (color);
}
