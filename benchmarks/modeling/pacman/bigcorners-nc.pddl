
(define (problem bigcorners-nc)
  (:domain pacman)
  (:objects
    bigcorners-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) bigcorners-nc)
	(= (at the_pacman) 1017)
	(= (collected) 0)
	(pellet_at 73)
	(pellet_at 1297)
	(pellet_at 1331)
	(pellet_at 39)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 4)
	)
  )

  

  (:bounds (location - int[1..1369]) (score - int[0..4]))

  
)
