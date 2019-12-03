#define TK1 TK_DEF // def
#define TK2 TK_IF // if
#define TK3 TK_OPEN_PARENTESI // (
#define TK4 TK_CLOSE_PARENTESI // )
#define TK5 TK_TWO_DOTS // :
#define TK6 TK_INDENT // ident
#define TK7 TK_IDENTIFIER // id
#define TK8 TK_COMA // ,
#define TK9 TK_ATTR // =
#define TK10 TK_PLUS_IGUAL // +=
#define TK11 TK_MINUS_IGUAL // -=
#define TK12 TK_MUL_IGUAL // *=
#define TK13 TK_DIV_IGUAL // /=
#define TK14 14 // (id_List)
#define TK15 15 // id_Add
#define TK16 TK_DEDENT // dedent
#define TK17 TK_WHILE // while
#define TK18 TK_IN // in
#define TK19 TK_NUMBER // integer
#define TK20 TK_ELSE // else
#define TK21 TK_ELIF // elif
#define TK22 TK_SUM_SUM // ++
#define TK23 TK_SUB_SUB // --
#define TK24 24 // add_cond
#define TK25 TK_E // &
#define TK26 TK_GREATER // >
#define TK27 TK_LOWER // <
#define TK28 TK_GREATER_EQUAL // >=
#define TK29 TK_LOWER_EQUAL // <=
#define TK30 TK_IGUAL // ==
#define TK31 TK_DIFF // !=
#define TK32 TK_NUMBER // number
#define TK33 TK_STRING // string
#define TK34 TK_SUM // +
#define TK35 TK_SUB // -
#define TK36 TK_MUL // *
#define TK37 TK_DIV // /
#define TK38 TK_Z // ^
#define TK39 TK_AND // and
#define TK40 TK_OR // or
#define TK41 41 // eof
#define TK42 TK_PRINT // print

int S();

int List_Param();

int Param();

int Param_add();

int St();

int Attr();

int Func();

int id_List();

int id_Add();

int If_Cmd();

int While_Cmd();

int For_Cmd();

int Else_Elif();

int Auto_Op();

int RAuto();

int List_Cond();

int add_cond();

int Expr_Cond();

int Expr();

int Type();

int RExpr();

int EndMarker();

int Print();

int RPrint();

int List_Print();

int Print_add();

int tkSintatico;

void getTokenSintatico();

//S -> def if ( List_Param ) : ident St EndMarker
int S(){
	if(tkSintatico == TK1){// def
		getTokenSintatico();
		if(tkSintatico == TK7){// id
			getTokenSintatico();
			if(tkSintatico == TK3){// (
				getTokenSintatico();
				if (Param()) {
					if(tkSintatico == TK4){// )
						getTokenSintatico();
						if(tkSintatico == TK5){// :
							getTokenSintatico();
							if (tkSintatico == TK_NEWLINE) {
								getTokenSintatico();
								if (tkSintatico == TK_INDENT) {
									getTokenSintatico();
									printf("Chegou: %d\n", tkSintatico);
									if (St()) {
										printf("Chegou 2: %d\n", tkSintatico);
										if (EndMarker()){
											return 1;
										}
										else{return 0;}
									}
									else{return 0;}
								}
								else{return 0;}
							}
							else{return 0;}
						}
						else{return 0;}
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//List_Param -> ( Param )
int List_Param(){
	if(tkSintatico == TK3){// (
		getTokenSintatico();
		if (Param()){
			if(tkSintatico == TK4){// )
				getTokenSintatico();
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Param -> Type id Param_add | ?
int Param(){
	if(Type()){
		if(tkSintatico == TK7){// id
			getTokenSintatico();
			if (Param_add()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Param_add -> , Param | ?
int Param_add(){
	if(tkSintatico == TK8){// ,
		getTokenSintatico();
		if (Param()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//St -> Func St | If_Cmd St | While_Cmd St | For_Cmd St | Attr St | Auto_Op St | ?
int St(){
	if(Func()){
		if (St()){
			return 1;
		}
		else{return 0;}
	}
	else if(If_Cmd()){
		if (St()){
			return 1;
		}
		else{return 0;}
	}
	else if(While_Cmd()){
		if (St()){
			return 1;
		}
		else{return 0;}
	}
	else if(For_Cmd()){
		if (St()){
			return 1;
		}
		else{return 0;}
	}
	else if(Attr()){
		if (St()){
			return 1;
		}
		else{return 0;}
	}
	else if(Auto_Op()){
		if (St()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Attr -> id = Func | id = Expr | id += Expr | id -= Expr | id *= Expr | id /= Expr
int Attr() {
	if (tkSintatico == TK7) {// id
		getTokenSintatico();
		if (tkSintatico == TK9) { // =
			getTokenSintatico();
			if (Func()) {
				return 1;
			} else if (Expr()) {
				return 1;
			} else {
				return 0;
			}
		} else if (tkSintatico == TK10) { // -=
			getTokenSintatico();
			if (Expr()) {
				return 1;
			} else {
				return 0;
			}
		} else if (tkSintatico == TK11) { // *=
			getTokenSintatico();
			if (Expr()) {
				return 1;
			} else {
				return 0;
			}
		} else if (tkSintatico == TK12) { // /=
			getTokenSintatico();
			if (Expr()) {
				return 1;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

//Func -> id (id_List)
int Func(){
	if(tkSintatico == TK7){// id
		getTokenSintatico();
		if(tkSintatico == TK14){// (id_List)
			getTokenSintatico();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//id_List -> id id_Add | ?
int id_List(){
	if(tkSintatico == TK7){// id
		getTokenSintatico();
		if(tkSintatico == TK15){// id_Add
			getTokenSintatico();
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//id_Add -> , id id_Add | ?
int id_Add(){
	if(tkSintatico == TK8){// ,
		getTokenSintatico();
		if(tkSintatico == TK7){// id
			getTokenSintatico();
			if(tkSintatico == TK15){// id_Add
				getTokenSintatico();
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//If_Cmd -> if ( List_Cond ) ident St dedent Else_Elif
int If_Cmd(){
	if(tkSintatico == TK2){// if
		getTokenSintatico();
		if(tkSintatico == TK3){// (
			getTokenSintatico();
			if (List_Cond()){
				if(tkSintatico == TK4){// )
					getTokenSintatico();
					if(tkSintatico == TK6){// ident
						getTokenSintatico();
						if (St()){
							if(tkSintatico == TK16){// dedent
								getTokenSintatico();
								if (Else_Elif()){
									return 1;
								}
								else{return 0;}
							}
							else{return 0;}
						}
						else{return 0;}
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//While_Cmd -> while ( List_Cond ) ident St dedent
int While_Cmd(){
	if(tkSintatico == TK17){// while
		getTokenSintatico();
		if(tkSintatico == TK3){// (
			getTokenSintatico();
			if (List_Cond()){
				if(tkSintatico == TK4){// )
					getTokenSintatico();
					if(tkSintatico == TK6){// ident
						getTokenSintatico();
						if (St()){
							if(tkSintatico == TK16){// dedent
								getTokenSintatico();
								return 1;
							}
							else{return 0;}
						}
						else{return 0;}
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//For_Cmd -> id in id ( integer ) ident St dedent
int For_Cmd(){
	if(tkSintatico == TK7){// id
		getTokenSintatico();
		if(tkSintatico == TK18){// in
			getTokenSintatico();
			if(tkSintatico == TK7){// id
				getTokenSintatico();
				if(tkSintatico == TK3){// (
					getTokenSintatico();
					if(tkSintatico == TK19){// integer
						getTokenSintatico();
						if(tkSintatico == TK4){// )
							getTokenSintatico();
							if(tkSintatico == TK6){// ident
								getTokenSintatico();
								if (St()){
									if(tkSintatico == TK16){// dedent
										getTokenSintatico();
										return 1;
									}
									else{return 0;}
								}
								else{return 0;}
							}
							else{return 0;}
						}
						else{return 0;}
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Else_Elif -> else ident St dedent | elif If_Cmd | ?
int Else_Elif(){
	if(tkSintatico == TK20){// else
		getTokenSintatico();
		if(tkSintatico == TK6){// ident
			getTokenSintatico();
			if (St()){
				if(tkSintatico == TK16){// dedent
					getTokenSintatico();
					return 1;
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tkSintatico == TK21){// elif
		getTokenSintatico();
		if (If_Cmd()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Auto_Op -> ++ id | -- id | id RAuto
int Auto_Op(){
	if(tkSintatico == TK22){// ++
		getTokenSintatico();
		if(tkSintatico == TK7){// id
			getTokenSintatico();
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK23){// --
		getTokenSintatico();
		if(tkSintatico == TK7){// id
			getTokenSintatico();
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK7){// id
		getTokenSintatico();
		if (RAuto()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//RAuto -> ++ | --
int RAuto(){
	if(tkSintatico == TK22){// ++
		getTokenSintatico();
		return 1;
	}
	else if(tkSintatico == TK23){// --
		getTokenSintatico();
		return 1;
	}
	else{return 0;}
}

//List_Cond -> Expr_Cond add_cond
int List_Cond(){
	if(Expr_Cond()){
		if(tkSintatico == TK24){// add_cond
			getTokenSintatico();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//add_cond -> & Expr_Cond | Expr_Cond | ?
int add_cond(){
	if(tkSintatico == TK25){// &
		getTokenSintatico();
		if (Expr_Cond()){
			return 1;
		}
		else{return 0;}
	}
	else if (Expr_Cond()){
		return 1;
	}
	else {return 1;}
}

//Expr_Cond -> Expr > Expr | Expr < Expr | Expr >= Expr | Expr <= Expr | Expr == Expr | Expr != Expr
int Expr_Cond(){
	if(Expr()){
		if(tkSintatico == TK26){// >
			getTokenSintatico();
			if (Expr()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Expr()){
		if(tkSintatico == TK27){// <
			getTokenSintatico();
			if (Expr()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Expr()){
		if(tkSintatico == TK28){// >=
			getTokenSintatico();
			if (Expr()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Expr()){
		if(tkSintatico == TK29){// <=
			getTokenSintatico();
			if (Expr()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Expr()){
		if(tkSintatico == TK30){// ==
			getTokenSintatico();
			if (Expr()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Expr()){
		if(tkSintatico == TK31){// !=
			getTokenSintatico();
			if (Expr()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expr -> id RExpr | ( Expr ) | Type
int Expr() {
	if (tkSintatico == TK7) {// id
		return 1;
	} else if(tkSintatico == TK3) {// (
		getTokenSintatico();
		if (Expr()) {
			if (tkSintatico == TK4) {// )
				return 1;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	} else if (Type()) {
		return 1;
	} else {
		return 0;
	}
}

//Type -> number | string
int Type(){
	if(tkSintatico == TK32){// number
		getTokenSintatico();
		return 1;
	}
	else if(tkSintatico == TK33){// string
		getTokenSintatico();
		return 1;
	}
	else{return 0;}
}

//RExpr -> + Expr | - Expr | * Expr | / Expr | ^ Expr | and Expr | or Expr
int RExpr(){
	if(tkSintatico == TK34){// +
		getTokenSintatico();
		if (Expr()){
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK35){// -
		getTokenSintatico();
		if (Expr()){
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK36){// *
		getTokenSintatico();
		if (Expr()){
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK37){// /
		getTokenSintatico();
		if (Expr()){
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK38){// ^
		getTokenSintatico();
		if (Expr()){
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK39){// and
		getTokenSintatico();
		if (Expr()){
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK40){// or
		getTokenSintatico();
		if (Expr()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//EndMarker -> dedent | eof
int EndMarker(){
	if(tkSintatico == TK16){// dedent
		getTokenSintatico();
		return 1;
	}
	else if(tkSintatico == TK41){// eof
		getTokenSintatico();
		return 1;
	}
	else{return 0;}
}

//Print -> print ( RPrint ) | print Print1Linha | print Print1Linha |
// int Print(){
// 	if(tkSintatico == TK42){// print
// 		getTokenSintatico();
// 		if(tkSintatico == TK3){// (
// 			getTokenSintatico();
// 			if (RPrint()){
// 				if(tkSintatico == TK4){// )
// 					getTokenSintatico();
// 					return 1;
// 				}
// 				else{return 0;}
// 			}
// 			else{return 0;}
// 		}
// 		else{return 0;}
// 	}
// 	else if(tkSintatico == TK42){// print
// 		getTokenSintatico();
// 		if (Print1Linha()){
// 			return 1;
// 		}
// 		else{return 0;}
// 	}
// 	else if(tkSintatico == TK42){// print
// 		getTokenSintatico();
// 		if (Print1Linha()){
// 			return 1;
// 		}
// 		else{return 0;}
// 	}
// 	else }

//RPrint -> List_Print | id
int RPrint(){
	if (List_Print()){
		return 1;
	}
	else if(tkSintatico == TK7){// id
		getTokenSintatico();
		return 1;
	}
	else{return 0;}
}

//List_Print -> string Print_add | id Print_add
int List_Print(){
	if(tkSintatico == TK33){// string
		getTokenSintatico();
		if (Print_add()){
			return 1;
		}
		else{return 0;}
	}
	else if(tkSintatico == TK7){// id
		getTokenSintatico();
		if (Print_add()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Print_add -> + string Print_add | + id Print_add | ?
int Print_add(){
	if(tkSintatico == TK34){// +
		getTokenSintatico();
		if(tkSintatico == TK33){// string
			getTokenSintatico();
			if (Print_add()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tkSintatico == TK34){// +
		getTokenSintatico();
		if(tkSintatico == TK7){// id
			getTokenSintatico();
			if (Print_add()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}
