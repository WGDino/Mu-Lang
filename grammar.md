$$
control + shift + v\\
...\\
\begin{align*}
NodeProgram &\to 
    \begin{cases}
        NodeFunction(Main)(stmnt^+)[1]\\
        NodeFunction(stmnt^+)
    \end{cases}
\\
NodeStmnt &\to 
    \begin{cases}
        return([NodeExpr]);\\
        NodeExpr(Token\ gives\ info ) = [NodeExpr]
    \end{cases}
\\
NodeExpr &\to 
    \begin{cases}
        int\_lit\\
        float\_lit\\
        char\_lit\\
        string\_lit\\
        identifier\\
        binary\_op
    \end{cases}
\end{align*}
$$