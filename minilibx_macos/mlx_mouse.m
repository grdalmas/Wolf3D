// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mlx_mouse.m                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/08/16 11:15:09 by banthony          #+#    #+#             //
//   Updated: 2018/08/16 11:17:30 by banthony         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


/*
**	Auteur: Olivier Crouzet
**	Gestion de la souris hors de la fenetre.
**	Recuperation de la position de la souris. (mouseover)
**	Code recuperer sur le forum de 42 -> Wolf3D -> Utiliser la libx
**	https://forum.intra.42.fr/topics/4680/messages/1#32384
*/

#include        <stdio.h>

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl3.h>

#include        "mlx_int.h"
#include        "mlx_new_window.h"

int     mlx_mouse_hide()
{
	//  CGDisplayHideCursor(kCGDirectMainDisplay);
	[NSCursor hide];
	return (0);
}

int     mlx_mouse_show()
{
	//  CGDisplayShowCursor(kCGDirectMainDisplay);
	[NSCursor unhide];
	return (0);
}

int     mlx_mouse_move(mlx_win_list_t *win, int x, int y)
{
	CGPoint       point;
	NSRect        pos;
	id    thewin;

	thewin = [(id)(win->winid) win];
	pos = [thewin frame];
	//  printf("got win pos %f %f\n", pos.origin.x, pos.origin.y);
	point.x = pos.origin.x + x;
	point.y = NSHeight([[thewin screen] frame]) - NSHeight([(id)(win->winid) frame]) - pos.origin.y + 1 + y;
	CGWarpMouseCursorPosition(point);
	CGAssociateMouseAndMouseCursorPosition(true);
	return (0);
}


int     mlx_mouse_get_pos(mlx_win_list_t *win, int *x, int *y)
{
	CGPoint       point;
	id            thewin;
	NSRect        pos;

	thewin = [(id)(win->winid) win];
	pos = [(id)(win->winid) frame];
	point = [thewin mouseLocationOutsideOfEventStream];
	*x = point.x;
	*y = NSHeight(pos) - 1 - point.y;
	return (0);
}
