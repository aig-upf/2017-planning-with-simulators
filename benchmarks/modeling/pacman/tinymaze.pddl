
(define (problem tinymaze)
  (:domain pacman)
  (:objects
    tinymaze - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) tinymaze)
	(= (at the_pacman) 13)
	(= (collected) 0)
	(pellet_at 37)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 1)
	)
  )

  

  (:bounds (location - int[1..49]) (score - int[0..1]))

  
)
