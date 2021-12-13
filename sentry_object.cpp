#define SENTRY_BUILD_STATIC 1
#include "thirdparty/sentry-native/include/sentry.h"

#include "core/config/project_settings.h"
#include "core/os/os.h"
#include "scene/main/scene_tree.h"
#include "scene/main/viewport.h"

#include "sentry_object.h"

// It is a singleton, it is always created automatically by register_types.cpp
Sentry *Sentry::singleton = NULL;

// _on_before_send callback is called after a crash but before it is sent to
// sentry
sentry_value_t _on_before_send(sentry_value_t event, void *hint,
                               void *closure) {

  // Flush Log file
  bool original_flush = ProjectSettings::get_singleton()->get_setting(
      "application/run/flush_stdout_on_print");
  Logger::set_flush_stdout_on_print(true);
  print_line("--- END godot.log ---");
  Logger::set_flush_stdout_on_print(original_flush);

  return event;
}

Sentry *Sentry::get_singleton() { return singleton; }

Sentry::Sentry() {
  singleton = this;

  // Get Project Settings
  String sentry_dsn = GLOBAL_DEF("third_party/sentry/dsn", String(""));
  String app_version =
      GLOBAL_DEF("third_party/sentry/app_version",
                 String("1.0")); // version of your game to report to Sentry
  send_ip_address = GLOBAL_DEF(
      "third_party/sentry/send_ip_address",
      false); // Turn on to include ip address of user in crash report
  String app_name =
      ProjectSettings::get_singleton()->get_setting("application/config/name");

  if (sentry_dsn == "") {
    if (!Engine::get_singleton()->is_editor_hint())
      print_line("Sentry not enabled. Set third_party/sentry/dsn in Project "
                 "Settings to enable.");
    return;
  }

  String sentry_db_path =
      OS::get_singleton()->get_user_data_dir() +
      "/.sentry-native"; // sentry needs a path it can write to
  app_name = app_name.to_lower().replace(" ", "-");         // slugify name
  String release = vformat("%s@%s", app_name, app_version); // ie game@1.0

  // Init Sentry
  sentry_options_t *options = sentry_options_new();
  sentry_options_set_dsn(options, sentry_dsn.utf8());
  sentry_options_set_release(options, release.utf8());
  sentry_options_set_database_path(options, sentry_db_path.utf8());
  sentry_options_set_before_send(options, _on_before_send, NULL);

  // Attach godot.log file to crash report.
  String data_dir = OS::get_singleton()->get_user_data_dir();
  sentry_options_add_attachment(options,
                                String(data_dir + "/logs/godot.log").utf8());

  sentry_init(options);

  // Add tags
  sentry_set_tag("app", app_name.utf8());
  String godot_version = Engine::get_singleton()->get_version_info()["string"];
  sentry_set_tag("godot_version", godot_version.utf8());

  // Optionally set default user that is just identified by ip
  if (send_ip_address) {
    sentry_value_t user = sentry_value_new_object();
    sentry_value_set_by_key(user, "ip_address",
                            sentry_value_new_string("{{auto}}"));
    sentry_set_user(user);
  }
}

Sentry::~Sentry() { sentry_close(); }

void Sentry::_bind_methods() {
  ClassDB::bind_method(D_METHOD("init"), &Sentry::_init);
  ClassDB::bind_method(D_METHOD("set_username"), &Sentry::_set_username);
	ClassDB::bind_method(D_METHOD("send_event"), &Sentry::_send_event);	
}

void Sentry::_init() {}

void Sentry::_set_username(String p_username) {
  sentry_remove_user(); // I don't know if it is important to remove previous
                        // user or not

  sentry_value_t user = sentry_value_new_object();
  if (send_ip_address) {
    sentry_value_set_by_key(user, "ip_address",
                            sentry_value_new_string("{{auto}}"));
  }
  sentry_value_set_by_key(user, "username",
                          sentry_value_new_string(p_username.utf8()));
  sentry_set_user(user);
}

void Sentry::_send_event(String p_text)
{
	sentry_capture_event(sentry_value_new_message_event(SENTRY_LEVEL_INFO, "custom", p_text.utf8()));
}
