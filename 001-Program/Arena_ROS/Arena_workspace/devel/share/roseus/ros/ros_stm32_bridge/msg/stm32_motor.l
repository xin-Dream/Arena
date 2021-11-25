;; Auto-generated. Do not edit!


(when (boundp 'ros_stm32_bridge::stm32_motor)
  (if (not (find-package "ROS_STM32_BRIDGE"))
    (make-package "ROS_STM32_BRIDGE"))
  (shadow 'stm32_motor (find-package "ROS_STM32_BRIDGE")))
(unless (find-package "ROS_STM32_BRIDGE::STM32_MOTOR")
  (make-package "ROS_STM32_BRIDGE::STM32_MOTOR"))

(in-package "ROS")
;;//! \htmlinclude stm32_motor.msg.html


(defclass ros_stm32_bridge::stm32_motor
  :super ros::object
  :slots (_pitch _yaw _roll ))

(defmethod ros_stm32_bridge::stm32_motor
  (:init
   (&key
    ((:pitch __pitch) 0.0)
    ((:yaw __yaw) 0.0)
    ((:roll __roll) 0.0)
    )
   (send-super :init)
   (setq _pitch (float __pitch))
   (setq _yaw (float __yaw))
   (setq _roll (float __roll))
   self)
  (:pitch
   (&optional __pitch)
   (if __pitch (setq _pitch __pitch)) _pitch)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:roll
   (&optional __roll)
   (if __roll (setq _roll __roll)) _roll)
  (:serialization-length
   ()
   (+
    ;; float64 _pitch
    8
    ;; float64 _yaw
    8
    ;; float64 _roll
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _pitch
       (sys::poke _pitch (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _roll
       (sys::poke _roll (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _pitch
     (setq _pitch (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _yaw
     (setq _yaw (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _roll
     (setq _roll (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get ros_stm32_bridge::stm32_motor :md5sum-) "6b33b81f528b84606cf372e61b6ef5ea")
(setf (get ros_stm32_bridge::stm32_motor :datatype-) "ros_stm32_bridge/stm32_motor")
(setf (get ros_stm32_bridge::stm32_motor :definition-)
      "float64 pitch
float64 yaw
float64 roll

")



(provide :ros_stm32_bridge/stm32_motor "6b33b81f528b84606cf372e61b6ef5ea")


