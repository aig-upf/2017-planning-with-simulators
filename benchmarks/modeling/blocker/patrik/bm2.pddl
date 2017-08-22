(define (problem binary_maze_2)
  (:domain blocker_fn_strips)
  (:objects n0 n1 n2 n3 n4 - node )
  (:init
    (exit n0)
    (exit n1)
    (edge n0 n2)
    (edge n2 n0)
    (edge n1 n3)
    (edge n3 n1)
    (edge n0 n3)
    (edge n3 n0)
    (edge n4 n2)
    (edge n2 n4)
    (edge n4 n3)
    (edge n3 n4)
    (= (cat) n4)
    (= (current_turn) blockers_turn)
   )

   (:goal
    (and (@trapped (cat)))
   )

   ;; maximum distance between two nodes in a graph G=(V,E)
   ;; is |V|-1
   (:bounds (distance - int[0..6]))

 )
