;;(with-open-file (*standard-output* "/dev/null" :direction :output
;;												:if-exists :supersede))

;; Convenient way to store the notice message
(defparameter *notice* "usage: sbcl --load game_of_life.lsp [-h] width height~%
positional arguments:
	width			width of the grid~%
	height			height of the grid~%
optional arguments:
	-h, --help		show this help message and exit~%"
	)

;; Prints the usage notice on incorrect arguments
(defun error-args()
	(format t *notice*)
	(sb-ext:exit))

;; Prints the usage notice on incorrect provided sizes
(defun error-size()
	(format t "Window size is too small (should be 10x10 at least)~%")
	(sb-ext:exit))

;; Fetch the arguments (discard the program's name')
(defparameter *arguments* (cdr *posix-argv*))

;; Check if there are exactly 2 arguments
(if (not (eq (length *arguments*) 2)) (error-args))

;; Check if the arguments are strict integers and no trailing caracters
(if (parse-integer (car *arguments*) :junk-allowed t)
	(if (parse-integer (reverse (car *arguments*)) :junk-allowed t)
		(if (parse-integer (car (cdr *arguments*)) :junk-allowed t)
			(if (not (parse-integer (reverse (car (cdr *arguments*))) :junk-allowed t))
				(error-args))
			(error-args))
		(error-args))
	(error-args))

;; Width & Height of the window
(defparameter *width* (parse-integer(car(cdr *posix-argv*))))
(defparameter *height* (parse-integer(car(cdr (cdr *posix-argv*)))))

;; Check if the size provided is within a correct range
(if (< *width* 40) (error-size))
(if (< *height* 40) (error-size))

;; Load SDL library
(ql:quickload "lispbuilder-sdl")
;; (ql:quickload '(:lispbuilder-sdl))

(defparameter *random-color* sdl:*white*)

;; Main
(defun main (argv)
	(sdl:with-init ()
		;; (sdl:window *width* *height* :title-caption "Move a rectangle using the mouse")
		(sdl:window 800 600 :title-caption "Carnifex: The Game of Life")
		(setf (sdl:frame-rate) 60)
		(sdl:with-events ()
			(:quit-event () t
						(sb-ext:exit))
			(:key-down-event ()
				(sdl:push-quit-event))
			(:idle ()
;; Change the color of the box if the left mouse button is depressed
				(when (sdl:mouse-left-p)
					(setf *random-color* (sdl:color :r (random 255) :g (random 255) :b (random 255))))
;; Clear the display each game loop
				(sdl:clear-display sdl:*black*)
;; Draw the box having a center at the mouse x/y coordinates.
				(sdl:draw-box (sdl:rectangle-from-midpoint-* (sdl:mouse-x) (sdl:mouse-y) 20 20)
																		:color *random-color*)
;; Redraw the display
				(sdl:update-display)))))

;; Run
(sb-int:with-float-traps-masked (:invalid :inexact :overflow)
	(main *posix-argv*))
