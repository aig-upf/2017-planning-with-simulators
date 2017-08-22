(define (problem corridor_3)
  (:domain helper_fn_strips)
  (:objects
    cat_0 - cat
    n_0_0 n_0_1 n_0_2  - node
  )
  (:init
    (exit n_0_0)
    (edge n_0_0 n_0_1) (edge n_0_1 n_0_0)
    (edge n_0_1 n_0_2) (edge n_0_2 n_0_1)
    (= (location cat_0) n_0_2)
    (= (view_range cat_0) 2)
   )

   (:goal
    (and
        (exit (location cat_0))
    )
   )

   (:bounds
    (distance - int[0..6])
   )

 )
