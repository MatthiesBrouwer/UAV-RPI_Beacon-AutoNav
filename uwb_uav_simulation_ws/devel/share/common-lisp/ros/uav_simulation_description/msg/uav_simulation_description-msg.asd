
(cl:in-package :asdf)

(defsystem "uav_simulation_description-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "uwb_data_raw" :depends-on ("_package_uwb_data_raw"))
    (:file "_package_uwb_data_raw" :depends-on ("_package"))
  ))