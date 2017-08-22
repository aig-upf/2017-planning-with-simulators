
(define (problem contoursmaze)
  (:domain pacman)
  (:objects
    contoursmaze - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) contoursmaze)
	(= (at the_pacman) 116)
	(= (collected) 0)
	(pellet_at 191)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 1)
	)
  )

  

  (:bounds (location - int[1..231]) (score - int[0..1]))

  
)
