
(define (problem tinysearch)
  (:domain pacman)
  (:objects
    tinysearch - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) tinysearch)
	(= (at the_pacman) 32)
	(= (collected) 0)
	(pellet_at 38)
	(pellet_at 11)
	(pellet_at 12)
	(pellet_at 44)
	(pellet_at 47)
	(pellet_at 16)
	(pellet_at 49)
	(pellet_at 17)
	(pellet_at 53)
	(pellet_at 23)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 10)
	)
  )

  

  (:bounds (location - int[1..63]) (score - int[0..10]))

  
)
