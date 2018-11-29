  (define lib (load-shared-object "./build/ig.so"))

  (define request
    (lambda (info)
        (let ((code (foreign-callable info (string string string) string)))
            (lock-object code)
            (foreign-callable-entry-point code))))

  (define ig_scheme_response
      (foreign-procedure "ig_scheme_response" (int string string string) string))

  (define response
    (lambda (status type content)
      (if (list? content)
        (ig_scheme_response status type (car content) (cadr content))
        (ig_scheme_response status type "" content))))

   (define ig_scheme_set
       (foreign-procedure "ig_scheme_set" (uptr uptr) int))

   (define ig_scheme_run
       (foreign-procedure "ig_scheme_run" (string int) int))

    (define-syntax set
        (syntax-rules ()
            ((_) '())
            ((_ (e1 e2) ...) (list (cons e1 e2) ...))))
 
    (define-syntax listen
        (syntax-rules ()
            ((_) '())
            ((_ e) (cond 
                        ((string? e) (list (cons 'ip e)))
                        ((integer? e) (list (cons 'port e)))
                        (else '())))
            ((_ e1 e2) (list (cons 'ip e1)(cons 'port e2)))))

    (define-syntax errorpage
        (syntax-rules ()
            ((_ e) (igr_errorpage e ""))
            ((_ e1 e2) (igr_errorpage e1 e2))))
 
    (define server 
        (lambda (get post set listen)
            (define ip "0.0.0.0") 
            (define port 8080)
            (ig_scheme_set get post)
            (ig_scheme_run ip port)))


(define get
    (lambda (header path query)
        (response 200 "text/html"
            (string-append "<p>path is:" path "</br>query is:" (if query query "nothing")))))
                
(define post
    (lambda (header path payload)
        (response 200 "application/json" "{\"hello\":\"world\"}")))

(server 
    (request get)
    (request post)
    (set)
    (listen))
