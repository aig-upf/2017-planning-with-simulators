
(define (problem mediumdottedmaze-nc)
  (:domain pacman)
  (:objects
    mediumdottedmaze-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) mediumdottedmaze-nc)
	(= (at the_pacman) 71)
	(= (collected) 0)
	(pellet_at 140)
	(pellet_at 141)
	(pellet_at 142)
	(pellet_at 284)
	(pellet_at 285)
	(pellet_at 286)
	(pellet_at 428)
	(pellet_at 429)
	(pellet_at 430)
	(pellet_at 578)
	(pellet_at 212)
	(pellet_at 213)
	(pellet_at 214)
	(pellet_at 605)
	(pellet_at 606)
	(pellet_at 607)
	(pellet_at 608)
	(pellet_at 609)
	(pellet_at 610)
	(pellet_at 356)
	(pellet_at 357)
	(pellet_at 358)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 22)
	)
  )

  

  (:bounds (location - int[1..648]) (score - int[0..22]))

  
)
