
(define (problem boxsearch)
  (:domain pacman)
  (:objects
    g0 g1 - ghost
	boxsearch - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) boxsearch)
	(= (at the_pacman) 119)
	(= (at g0) 125)
	(= (at g1) 55)
	(= (collected) 0)
	(pellet_at 128)
	(pellet_at 130)
	(pellet_at 132)
	(pellet_at 134)
	(pellet_at 136)
	(pellet_at 16)
	(pellet_at 18)
	(pellet_at 20)
	(pellet_at 22)
	(pellet_at 24)
	(pellet_at 156)
	(pellet_at 158)
	(pellet_at 160)
	(pellet_at 162)
	(pellet_at 164)
	(pellet_at 44)
	(pellet_at 46)
	(pellet_at 48)
	(pellet_at 50)
	(pellet_at 52)
	(pellet_at 72)
	(pellet_at 74)
	(pellet_at 76)
	(pellet_at 78)
	(pellet_at 80)
	(pellet_at 100)
	(pellet_at 102)
	(pellet_at 104)
	(pellet_at 106)
	(pellet_at 108)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 30)
	)
  )

  

  (:bounds (location - int[1..196]) (score - int[0..30]))

  
)
