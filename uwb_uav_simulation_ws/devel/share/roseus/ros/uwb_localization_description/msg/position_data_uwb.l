;; Auto-generated. Do not edit!


(when (boundp 'uwb_localization_description::position_data_uwb)
  (if (not (find-package "UWB_LOCALIZATION_DESCRIPTION"))
    (make-package "UWB_LOCALIZATION_DESCRIPTION"))
  (shadow 'position_data_uwb (find-package "UWB_LOCALIZATION_DESCRIPTION")))
(unless (find-package "UWB_LOCALIZATION_DESCRIPTION::POSITION_DATA_UWB")
  (make-package "UWB_LOCALIZATION_DESCRIPTION::POSITION_DATA_UWB"))

(in-package "ROS")
;;//! \htmlinclude position_data_uwb.msg.html


(defclass uwb_localization_description::position_data_uwb
  :super ros::object
  :slots (_destination_id _distance _stamp _uwb_position ))

(defmethod uwb_localization_description::position_data_uwb
  (:init
   (&key
    ((:destination_id __destination_id) (make-array 0 :initial-element 0 :element-type :integer))
    ((:distance __distance) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:stamp __stamp) (let (r) (dotimes (i 0) (push (instance ros::time :init) r)) r))
    ((:uwb_position __uwb_position) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _destination_id __destination_id)
   (setq _distance __distance)
   (setq _stamp __stamp)
   (setq _uwb_position __uwb_position)
   self)
  (:destination_id
   (&optional __destination_id)
   (if __destination_id (setq _destination_id __destination_id)) _destination_id)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:uwb_position
   (&optional __uwb_position)
   (if __uwb_position (setq _uwb_position __uwb_position)) _uwb_position)
  (:serialization-length
   ()
   (+
    ;; int64[] _destination_id
    (* 8    (length _destination_id)) 4
    ;; float64[] _distance
    (* 8    (length _distance)) 4
    ;; time[] _stamp
    (* 8    (length _stamp)) 4
    ;; float64[] _uwb_position
    (* 8    (length _uwb_position)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64[] _destination_id
     (write-long (length _destination_id) s)
     (dotimes (i (length _destination_id))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _destination_id i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _destination_id i)) (= (length ((elt _destination_id i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _destination_id i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _destination_id i) . bv) 1) -1) s))
             ((and (class (elt _destination_id i)) (= (length ((elt _destination_id i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _destination_id i) . bv) 0) s)
              (write-long (if (>= (elt _destination_id i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _destination_id i) s)(write-long (if (>= (elt _destination_id i) 0) 0 #xffffffff) s)))
       )
     ;; float64[] _distance
     (write-long (length _distance) s)
     (dotimes (i (length _distance))
       (sys::poke (elt _distance i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; time[] _stamp
     (write-long (length _stamp) s)
     (dotimes (i (length _stamp))
       (write-long (send (elt _stamp i) :sec) s) (write-long (send (elt _stamp i) :nsec) s)
       )
     ;; float64[] _uwb_position
     (write-long (length _uwb_position) s)
     (dotimes (i (length _uwb_position))
       (sys::poke (elt _uwb_position i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64[] _destination_id
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _destination_id (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _destination_id i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _destination_id i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;; float64[] _distance
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _distance (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _distance i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; time[] _stamp
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _stamp (let (r) (dotimes (i n) (push (instance ros::time :init) r)) r))
     (dolist (elem- _stamp)
     (send elem- :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send elem- :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;; float64[] _uwb_position
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _uwb_position (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _uwb_position i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get uwb_localization_description::position_data_uwb :md5sum-) "cffdb089f0ead7804716b039674b3438")
(setf (get uwb_localization_description::position_data_uwb :datatype-) "uwb_localization_description/position_data_uwb")
(setf (get uwb_localization_description::position_data_uwb :definition-)
      "int64[] destination_id
float64[] distance
time[] stamp
float64[] uwb_position

")



(provide :uwb_localization_description/position_data_uwb "cffdb089f0ead7804716b039674b3438")


