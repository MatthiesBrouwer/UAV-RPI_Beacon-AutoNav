
(cl:in-package :asdf)

(defsystem "test_simulation_description-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "uwb_data" :depends-on ("_package_uwb_data"))
    (:file "_package_uwb_data" :depends-on ("_package"))
  ))