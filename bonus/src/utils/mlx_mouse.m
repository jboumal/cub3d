#import <Cocoa/Cocoa.h>

int	mac_mouse_hide(void)
{
	[NSCursor hide];
	return (0);
}

int	mac_mouse_move(int x, int y)
{
	CGPoint	point;

	point.x = x;
	point.y = y;
	CGWarpMouseCursorPosition(point);
	CGAssociateMouseAndMouseCursorPosition(true);
	return (0);
}