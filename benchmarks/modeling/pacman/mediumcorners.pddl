
(define (problem mediumcorners)
  (:domain pacman)
  (:objects
    mediumcorners - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) mediumcorners)
	(= (at the_pacman) 366)
	(= (collected) 0)
	(pellet_at 32)
	(pellet_at 362)
	(pellet_at 59)
	(pellet_at 389)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 4)
	)
  )

  

  (:bounds (location - int[1..420]) (score - int[0..4]))

  
)
