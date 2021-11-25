
(cl:in-package :asdf)

(defsystem "ros_stm32_bridge-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "stm32_motor" :depends-on ("_package_stm32_motor"))
    (:file "_package_stm32_motor" :depends-on ("_package"))
  ))