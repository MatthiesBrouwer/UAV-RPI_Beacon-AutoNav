
(cl:in-package :asdf)

(defsystem "uwb_localization_description-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "position_data_uwb" :depends-on ("_package_position_data_uwb"))
    (:file "_package_position_data_uwb" :depends-on ("_package"))
    (:file "uwb_data_raw" :depends-on ("_package_uwb_data_raw"))
    (:file "_package_uwb_data_raw" :depends-on ("_package"))
  ))