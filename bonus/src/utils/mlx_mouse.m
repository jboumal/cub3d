#import <Cocoa/Cocoa.h>

int	mouse_hide(void)
{
	[NSCursor hide];
	return (0);
}

int	mouse_move(int x, int y)
{
	CGPoint	point;

	point.x = x;
	point.y = y;
	CGWarpMouseCursorPosition(point);
	CGAssociateMouseAndMouseCursorPosition(true);
	return (0);
}