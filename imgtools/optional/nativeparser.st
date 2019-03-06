Methods String 'all'
	doIt	| meth |
		meth <- <85 ('doIt ', self)>.
		^ meth notNil
			ifTrue: [ 
				"meth display."
				meth executeWith:#(0)
			]
            ifFalse:[
                ('cannot parser ', self) print 
            ]
]