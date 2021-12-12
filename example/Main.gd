extends Control


func _on_Crash_pressed():
	Sentry.test_crash()


func _on_SendEvent_pressed():
	Sentry.send_event("Test Event!")
