$$
control + shift + v\\
...\\
\begin{align*}
program &\to 
    \begin{cases}
        NodeFunction(Main)(stmnt^+)[1]\\
        NodeFunction(stmnt^+)
    \end{cases}
\\
stmnt &\to 
    \begin{cases}
        return([NodeExpr]);\\
        NodeExpr(Token) = [NodeExpr]
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