/*
 * IRC Mode Message Suppressing Plugin for libpurple
 *
 * Copyright (C) 2015, Joey Yandle <xoloki@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02111-1301, USA.
 */

#define PURPLE_PLUGINS

#include <string.h>

#include <account.h>
#include <accountopt.h>
#include <cmds.h>
#include <connection.h>
#include <conversation.h>
#include <debug.h>
#include <notify.h>
#include <plugin.h>
#include <pluginpref.h>
#include <prefs.h>
#include <util.h>
#include <version.h>

#include "plugin_config.h"

#define PLUGIN_STATIC_NAME "ircnomode"
#define PLUGIN_ID "core-xoloki-" PLUGIN_STATIC_NAME

#define PLUGIN_AUTHOR      "Joey Yandle <xoloki@gmail.com>"


/*****************************************************************************
 * Constants                                                                 *
 *****************************************************************************/

#define IRC_PLUGIN_ID "prpl-irc"

#define MESSAGE_MODE "mode ("

/*****************************************************************************
 * Prototypes                                                                *
 *****************************************************************************/

static gboolean plugin_load(PurplePlugin *plugin);
static gboolean plugin_unload(PurplePlugin *plugin);


/*****************************************************************************
 * Plugin Info                                                               *
 *****************************************************************************/

static PurplePluginInfo info =
{
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	0,
	PURPLE_PLUGIN_STANDARD,          /**< type           */
	NULL,                            /**< ui_requirement */
	0,                               /**< flags          */
	NULL,                            /**< dependencies   */
	PURPLE_PRIORITY_DEFAULT,         /**< priority       */
	PLUGIN_ID,                       /**< id             */
	NULL,                            /**< name           */
	PLUGIN_VERSION,                      /**< version        */
	NULL,                            /**< summary        */
	NULL,                            /**< description    */
	PLUGIN_AUTHOR,	                 /**< author         */
	PLUGIN_WEBSITE,                      /**< homepage       */
	plugin_load,                     /**< load           */
	plugin_unload,                   /**< unload         */
	NULL,                            /**< destroy        */

	NULL,                            /**< ui_info        */
	NULL,                            /**< extra_info     */
	NULL,                            /**< prefs_info     */
	NULL,                            /**< actions        */
	NULL,                            /**< reserved 1     */
	NULL,                            /**< reserved 2     */
	NULL,                            /**< reserved 3     */
	NULL                             /**< reserved 4     */
};

/*****************************************************************************
 * Callbacks                                                                 *
 *****************************************************************************/

static gboolean writing_chat_msg_cb(PurpleAccount *account, const char *who,
                                    char **message, PurpleConversation *conv,
                                    PurpleMessageFlags flags)
{
	if (!g_str_equal(purple_account_get_protocol_id(account), IRC_PLUGIN_ID))
		return FALSE;

	if (NULL == *message)
		return FALSE;

	g_return_val_if_fail(purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_CHAT, FALSE);


	if ((flags & PURPLE_MESSAGE_SYSTEM) && g_str_has_prefix(*message, MESSAGE_MODE))
    {
        return TRUE;
    }

	return FALSE;
}

/*****************************************************************************
 * Plugin Code                                                               *
 *****************************************************************************/

static gboolean plugin_load(PurplePlugin *plugin)
{
	PurplePlugin *irc_prpl;
	PurplePluginProtocolInfo *prpl_info;
	void *conv_handle;

	irc_prpl = purple_plugins_find_with_id(IRC_PLUGIN_ID);

	if (NULL == irc_prpl)
		return FALSE;

	prpl_info = PURPLE_PLUGIN_PROTOCOL_INFO(irc_prpl);
	if (NULL == prpl_info)
		return FALSE;

	/* Register callbacks. */

	conv_handle = purple_conversations_get_handle();

	purple_signal_connect(conv_handle, "writing-chat-msg",
	                    plugin, PURPLE_CALLBACK(writing_chat_msg_cb), NULL);

	return TRUE;
}

static gboolean plugin_unload(PurplePlugin *plugin)
{
	PurplePlugin *irc_prpl;
	PurplePluginProtocolInfo *prpl_info;

	irc_prpl = purple_plugins_find_with_id(IRC_PLUGIN_ID);
	if (NULL == irc_prpl)
		return FALSE;

	prpl_info = PURPLE_PLUGIN_PROTOCOL_INFO(irc_prpl);
	if (NULL == prpl_info)
		return FALSE;

	return TRUE;
}

static void plugin_init(PurplePlugin *plugin)
{
	info.dependencies = g_list_append(info.dependencies, IRC_PLUGIN_ID);

	info.name = "IRC No-Mode";
	info.summary = "Suppresses mode changes, especially useful for slack.";
	info.description = "Suppresses mode changes, especially useful for slack.";
}

PURPLE_INIT_PLUGIN(PLUGIN_STATIC_NAME, plugin_init, info)
