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

#include "wldictwindow.h"
#include "wldictsession.h"

#define BAIDU_FANYI_LOGO PACKAGE_DATA_DIR "/baidu-fanyi.png"

G_DEFINE_TYPE(WlDictWindow, wl_dict_window, GTK_TYPE_WINDOW);

static void wl_dict_window_init(WlDictWindow *obj);
static void wl_dict_window_finalize(GObject *obj);
static void wl_dict_window_class_init(WlDictWindowClass *klass);
static void wl_dict_window_getter(GObject *object,guint property_id,
                                  GValue *value,GParamSpec *ps);
static void wl_dict_window_setter(GObject *object,guint property_id,
                                  const GValue *value,GParamSpec *ps);

static void onQuitItemActivate(GtkMenuItem *item,gpointer data);
static void onAboutItemActivate(GtkMenuItem *item,gpointer data);
static gboolean onWindowDelete(GtkWidget *widget,GdkEvent *event,gpointer data);
static void onCheckItemActivate(GtkCheckMenuItem *item,gpointer data);
static void onSearchButtonClicked(GtkButton *button,gpointer data);

static inline void showDictWindow(WlDictWindow *window);
static inline void hideDictWindow(WlDictWindow *window);

static void wl_dict_window_init(WlDictWindow *obj)
{
    gtk_window_set_resizable (GTK_WINDOW(obj),FALSE);
    gtk_window_set_keep_above (GTK_WINDOW(obj),TRUE);
    g_signal_connect(G_OBJECT(obj),"delete-event",
                     G_CALLBACK(onWindowDelete),obj);

    GtkWidget *box=gtk_box_new (GTK_ORIENTATION_HORIZONTAL,5);
    gtk_container_add(GTK_CONTAINER(obj),box);
    /* entry */
    GtkWidget *entry=gtk_entry_new ();
    gtk_entry_set_activates_default(GTK_ENTRY(entry),TRUE);
    gtk_box_pack_start (GTK_BOX(box),entry,TRUE,TRUE,0);
    /* button */
    GtkWidget *button=gtk_button_new_with_label ("query");
    gtk_widget_set_can_default (button,TRUE);
    gtk_window_set_default (GTK_WINDOW(obj),button);
    g_signal_connect(G_OBJECT(button),"clicked",
                     G_CALLBACK(onSearchButtonClicked),obj);
    gtk_box_pack_start (GTK_BOX(box),button,FALSE,TRUE,0);

    /* indicator */
    AppIndicator *ci=app_indicator_new("wdict","search",APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_status(ci,APP_INDICATOR_STATUS_ACTIVE);

    /* indicator menu */
    GtkWidget *menu=gtk_menu_new();
	    app_indicator_set_menu(ci,GTK_MENU(menu));
    GtkWidget *checkItem=gtk_check_menu_item_new ();
    gtk_menu_item_set_label (GTK_MENU_ITEM(checkItem),"Show/Hide");
    g_signal_connect(G_OBJECT(checkItem),"activate",
                     G_CALLBACK(onCheckItemActivate),obj);
    gtk_menu_shell_append (GTK_MENU_SHELL(menu),checkItem);
	GtkWidget *aboutItem=gtk_menu_item_new_with_label ("About");
	g_signal_connect(G_OBJECT(aboutItem),"activate",
	                 G_CALLBACK(onAboutItemActivate),NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu),aboutItem);
    GtkWidget *quitItem=gtk_menu_item_new_with_label ("Quit");
    g_signal_connect(G_OBJECT(quitItem),"activate",
                     G_CALLBACK(onQuitItemActivate),obj);
    gtk_menu_shell_append (GTK_MENU_SHELL(menu),quitItem);
    gtk_widget_show_all (menu);

    obj->textEntry=entry;
    obj->bdButton=button;
    obj->ai=ci;
    obj->checkItem=checkItem;
    obj->query=wl_dict_query_new (WL_DICT_AUTO,WL_DICT_AUTO);
}

static void wl_dict_window_finalize(GObject *obj)
{
    WlDictWindow *window=WL_DICT_WINDOW(obj);
    g_object_unref(window->ai);
}

static void wl_dict_window_class_init(WlDictWindowClass *klass)
{
    GObjectClass *obj_class=G_OBJECT_CLASS(klass);
    obj_class->get_property=wl_dict_window_getter;
    obj_class->set_property=wl_dict_window_setter;
    obj_class->finalize=wl_dict_window_finalize;

    GParamSpec *ps;
    /* properties */
}

static void wl_dict_window_getter(GObject *object,guint property_id,
                                  GValue *value,GParamSpec *ps)
{
    WlDictWindow *obj=WL_DICT_WINDOW(object);
    switch(property_id) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,ps);
    }
}

static void wl_dict_window_setter(GObject *object,guint property_id,
                                  const GValue *value,GParamSpec *ps)
{
    WlDictWindow *obj=WL_DICT_WINDOW(object);
    switch(property_id) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,ps);
    }
}

static void onQuitItemActivate(GtkMenuItem *item,gpointer data)
{
    WlDictWindow *window=WL_DICT_WINDOW(data);

    gtk_widget_destroy (GTK_WIDGET(window));
    //g_object_unref(window->ai);
    gtk_main_quit ();
}

static gboolean onWindowDelete(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    WlDictWindow *window=WL_DICT_WINDOW(data);
    hideDictWindow(window);
    return TRUE;
}

static void onCheckItemActivate(GtkCheckMenuItem *item,gpointer data)
{
    if(gtk_check_menu_item_get_active(item)) {
        gtk_window_set_position (GTK_WINDOW(data),GTK_WIN_POS_MOUSE);
        gtk_widget_show_all (GTK_WIDGET(data));
    } else {
        gtk_widget_hide (GTK_WIDGET(data));
    }
}

static void onQueryCallback(WlDictLang from,WlDictLang to,
                            const gchar *src,const gchar *res,
                            gpointer data,GError *err)
{
    if(err) {
        g_warning("%s",err->message);
        return;
    }
    g_printf("%s=>%s\n\t%s:%s\n",wl_dict_lang_get_phrase (from),
             wl_dict_lang_get_phrase (to),src,res);
}

static void onSearchButtonClicked(GtkButton *button,gpointer data)
{
    WlDictWindow *window=WL_DICT_WINDOW(data);

    gtk_widget_grab_focus (window->textEntry);
    gtk_editable_select_region (GTK_EDITABLE(window->textEntry),0,-1);

    const gchar *src=gtk_entry_get_text (GTK_ENTRY(window->textEntry));
    wl_dict_query_query (window->query,src,onQueryCallback ,NULL);
}

static inline GdkPixbuf *getBaiduLogo(void)
{
	GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file (BAIDU_FANYI_LOGO,NULL);
	if(pixbuf==NULL)
		pixbuf=gdk_pixbuf_new_from_file (PACKAGE_SRC_DIR "/../data/baidu-fanyi.png",NULL);
	return pixbuf;
}

static void onAboutItemActivate(GtkMenuItem *item,gpointer data)
{
	const gchar *authors[]={
		"Wiky L(wiiiky@yeah.net)",
		NULL
	};
	GtkWidget *dialog=gtk_about_dialog_new ();
	/* TODO */
	gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG(dialog),getBaiduLogo ());
	gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(dialog),GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"Copyright (c) 2014 - 2014 Wiky L");
	gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(dialog),authors);
	gtk_about_dialog_set_website (GTK_ABOUT_DIALOG(dialog),"https://launchpad.net/~wiiiky-v");
	gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG(dialog),"Based on Baidu Fanyi API");
	//gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(dialog),FALSE);

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy (dialog);
}

static inline void showDictWindow(WlDictWindow *window)
{
    gtk_window_set_position (GTK_WINDOW(window),GTK_WIN_POS_MOUSE);
    gtk_widget_show_all (GTK_WIDGET(window));
    gtk_widget_grab_focus (window->textEntry);
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM(window->checkItem),TRUE);
}
static inline void hideDictWindow(WlDictWindow *window)
{
    gtk_widget_hide (GTK_WIDGET(window));
    gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM(window->checkItem),FALSE);
}

/**************************************************
 * PUBILC
 **************************************************/
WlDictWindow *wl_dict_window_new(void)
{
    WlDictWindow *window=(WlDictWindow*)g_object_new (WL_TYPE_DICT_WINDOW,NULL);


    showDictWindow (window);
    return window;
}
