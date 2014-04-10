/*
 * Copyright (C) 2014-2014 Wiky L(wiiiky@yeah.net)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * this file is generated by gobj(https://github.com/wiiiky/gobj)
 */

#ifndef __WL_DICT_WINDOW_H__
#define __WL_DICT_WINDOW_H__

#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include "wldictquery.h"

G_BEGIN_DECLS
/* Macro for casting a pointer to a WlDictWindow or WlDictWindowClass pointer.
 * Macros for testing whether `object' or `klass' are of type WL_TYPE_DICT_WINDOW.
 */
#define WL_TYPE_DICT_WINDOW	(wl_dict_window_get_type())
#define WL_DICT_WINDOW(obj)	(G_TYPE_CHECK_INSTANCE_CAST ((obj), WL_TYPE_DICT_WINDOW, WlDictWindow))
#define WL_DICT_WINDOW_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), WL_TYPE_DICT_WINDOW, WlDictWindowClass))
#define WL_IS_DICT_WINDOW(obj)	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), WL_TYPE_DICT_WINDOW))
#define WL_IS_DICT_WINDOW_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), WL_TYPE_DICT_WINDOW))
#define WL_DICT_WINDOW_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), WL_TYPE_DICT_WINDOW, WlDictWindowClass))
typedef struct _WlDictWindow WlDictWindow;
typedef struct _WlDictWindowClass WlDictWindowClass;


struct _WlDictWindow {
	GtkWindow parent;
	/*Private */
	GtkWidget *textEntry;
	GtkWidget *bdButton;
	AppIndicator *ai;
	GtkWidget *checkItem;

	WlDictQuery *query;
};

struct _WlDictWindowClass {
	GtkWindowClass parentKlass;
	/*Private */
};

GType wl_dict_window_get_type(void) G_GNUC_CONST;

/* Public */
WlDictWindow *wl_dict_window_new(void);


G_END_DECLS
#endif
