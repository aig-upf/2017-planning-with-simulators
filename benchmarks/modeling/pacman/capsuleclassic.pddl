
(define (problem capsuleclassic)
  (:domain pacman)
  (:objects
    g0 g1 g2 - ghost
	capsuleclassic - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) capsuleclassic)
	(= (at the_pacman) 104)
	(= (at g0) 21)
	(= (at g1) 30)
	(= (at g2) 113)
	(= (collected) 0)
	(pellet_at 22)
	(pellet_at 34)
	(pellet_at 35)
	(pellet_at 36)
	(pellet_at 37)
	(pellet_at 40)
	(pellet_at 53)
	(pellet_at 56)
	(pellet_at 59)
	(pellet_at 72)
	(pellet_at 75)
	(pellet_at 78)
	(pellet_at 82)
	(pellet_at 91)
	(pellet_at 92)
	(pellet_at 94)
	(pellet_at 97)
	(pellet_at 98)
	(pellet_at 99)
	(pellet_at 100)
	(pellet_at 101)
	(pellet_at 110)
	(pellet_at 111)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 23)
	)
  )

  

  (:bounds (location - int[1..133]) (score - int[0..23]))

  
)
