- main函数里面就是查看文件里面的所有token
  - new一个Lexer，然后不断调用lexer的next_token函数，直到读取到EOF

词法解析，语法解析出ast抽象语法树

(1.2 + 1) * 2

1 + 2 * 3



Expression_Statement继承自Statement，但是它有一个expression指针

所以它是连接statement和expression的桥梁

Program类里面list< shared_ptr< Statement > >，这里的Statement其实是一个Expression_Statement

 

报错机制：parser会识别到错误的语法结构，然后会保存在parser的vector< string >m_errors里面去，而evaluator使用error的object类型来报错



- Token类	

  - 成员变量

    - Type m_type;
      - 这个Token对象的类型
    - string m_literal;
      - 这个Token对象的文字信息
    - static std::map<Type, string> m_name;
      - 标注每种Token类型的名字

  - 类内定义了Token::Type

    - 

    ```
    enum Type
    {
        TOKEN_ILLEGAL = 0,
        TOKEN_INTEGER,
        TOKEN_FLOAT,
        TOKEN_EOF,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_ASTERISK,
        TOKEN_SLASH,
        TOKEN_MODULO,
        TOKEN_TILDE,
        TOKEN_BIT_AND,
        TOKEN_BIT_OR,      //|
        TOKEN_BIT_XOR,     //^
        TOKEN_BIT_LSHIFT,  // <<
        TOKEN__BIT_RSHIFT, // >>
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_SEMICOLON,
    };
    ```

  - 构造函数

    - Token::Token() : m_type(TOKEN_ILLEGAL)
      - 空参数就是illegal
    - Token::Token(pi::token::Token::Type type, const std::string& literal) : m_type(type), m_literal(literal)
      - 用Token的类型和文本定义一个Token
    - Token::Type Token::type()
      - 返回类型
    - string Token::name() 
      - 返回Token的类型在m_name中对应的名字
    - string Token::literal()
      - 返回该Token的文本
    - string Token::show()
      - 返回该Token的文本和类型名字
    - Json Token::json() 
      - type对应类型
      - name对应文本

- Lexer类

  - 成员变量

    - string m_input;
      - 当前的文件
    - char m_ch;
      - 当前查看的字符
    - int m_pos;
      - 当前的位置
    - int m_next_pos;
      - 下一个位置

  - 构造函数

    - ```
      Lexer::Lexer() {
          m_ch = 0;
          m_pos = 0;
          m_next_pos = 0;
      }
      ```

    - Lexer::Lexer(const std::string &file) 

      - 从这个文件里面把字符提取到m_input里面

    - Lexer::Lexer(const char *buf, int len)

      - 从一个字符数组里面拷贝到m_input

    - void Lexer::read_char()

      - 去读取下一个字符存到m_ch里面
      - 然后更新m_pos、m_next_pos

    - char Lexer::peek_char()

      - 返回下一个位置的字符，也就是瞥一眼

    - void Lexer::unread_char()

      - m_pos、m_next_pos位置回退一格

    - void Lexer::skip_white_space()

      - 忽略空格字符\t \n和空格

    - bool Lexer::is_digit(char ch) 

      - 是否为数字

    - string Lexer::read_number()

      - 读取数字
      - 先存储当前位置，然后看最多有多少个digit，最后使用substr取出这一串数字
      - 因为是不断调用read_char函数的，所以m_ch会更新为非数字位

    - Token Lexer::new_token(Token::Type type, const std::string &literal)

      - 给定type和文本，new一个Token返回

    - Token Lexer::next_token() 

      - 很复杂的函数
      - 返回m_input里面的下一个Token
      - 目前有+-*/%~()和EOF也就是0
        - 会new一个Token，把类型和文本记录进去然后返回
      - 如果不是上面这些符号的话。那就进default
        - 判断 m_ch是否为数字，如果是，就调用read_number,m_ch变成了非数字位
          - 如果m_ch当前为点.  并且下一个字符为数字位，那么就调用read_char，并且再次调用read_number找到小数部分fraction
          - 调用read_number函数之后 需要使用一个unread_char把位置回退
            - 因为next_token函数一开头就是会调用read_char()，所以必须把m_pos和m_next_pos的位置回退，m_ch是不会因为调用read_char函数而改变的
          - 
        - 如果什么都不是，就说明是illegal，把文本和ILLEGAL传进一个Token返回就好了

- ast文件夹

  - Node类

    - 所有抽象语法树的节点都是一个Node

      - Expression和Statement都继承自Node

    - 有一个Type

      - 

      ```
      enum Type
      {
          NODE_INTEGER = 0,
          NODE_FLOAT,
          NODE_INFIX,
          NODE_EXPRESSION_STATEMENT,
          NODE_PROGRAM,
          NODE_PREFIX,
      };
      ```

      - 保存着node的类型

    - 成员变量

      - Type m_type;
        - node的类型
      - Token m_token;
        - node对应的Token，比如中缀表达式加法就是一个+ token
      - static std::map<Type, string> m_names;
        - 对应的type的名字

    - string Node::name() const

      - 返回节点的类型名

  - program.h

    - Program类：继承自Statement
      - std::list< std::shared_ptr<Statement> > m_statement;
      - 有一系列的Statement指针

  - prefix.h

    - Prefix类
      - string m_operator;
      - std::shared_ptr<Expression> m_right;

  - integer.h

    - Integer类
      - int64_t m_values;

  - infix.h

    - Infix类
      - std::shared_ptr<Expression> m_left;
      - string m_operator;
      - std::shared_ptr<Expression> m_right;

  - expression_statement.h

    - Expression_Statement：继承自Statement
      - std::shared_ptr<Expression> m_expression;

  - 

- 

- Parser类

  - 定义了运算符优先级

    - ```
      enum Precedence
      {
          LOWEST = 0,
          SUM,   // + -
          PRODUCT, // *  /  %
          PREFIX, // -a  ~a  !a
      };
      ```

  - 成员变量

    - std::shared_ptr<Lexer> m_lexer;
      - 词法解析器，会在初始化的时候指定
    - Token m_curr;
      - 当前的Token
    - Token m_peek;
      - 下一个Token
    - std::list<string> m_errors;
      - 错误信息双向链表
    - static std::map<Token::Type, int> m_precedences;
      - Token类型对应的优先级
    - static std::map<Token::Type, prefix_parser_fn> m_prefix_parser_fns;
      - 前缀的Token类型对应的回调函数
    - static std::map<Token::Type, infix_parser_fn> m_infix_parser_fns;
      - 中缀的Token类型对应的回调函数

  - 构造函数

    - Parser::Parser(std::shared_ptr<Lexer> &lexer) : m_lexer(lexer)
      - 初始化lexer
    - 并且调用两次next_token()

  - std::shared_ptr<Program> Parser::parse_program()

    - 在program.cpp
    - 

  - void Parser::next_token()

    - 让m_curr变成m_peek
    - 让m_peek等于lexer的next_token

  - bool Parser::curr_token_is(Token::Type type)

    - 判断m_curr的类型是不是type

  - bool Parser::peek_token_is(Token::Type type)

    - 判断m_peek的类型是不是type

  - bool Parser::expect_peek_token(Token::Type type)

    - 如果m_peek的类型是type，那么就调用next_token
    - 否则报错（m_peek的类型应该是type，但是不是，所以报错

  - void Parser::peek_error(Token::Type type) 

    - m_peek的类型应该是type，但是不是，所以报错
    - m_errors插入这一条报错的string

  - int Parser::curr_token_precedence()

    - 返回m_curr的优先级
    - 先在m_precedences里面找m_curr的类型对应的优先级，找不到就返回LOWEST

  - int Parser::peek_token_precedence()

    - 返回m_peek 的优先级

  - void Parser::no_prefix_parse_fn_error(Token::Type type)

    - 没有这个类型的prefix回调函数错误
    - 插入到m_errors里面

  - std::list<string> & Parser::errors()

    - 返回m_errors

  - ```
    typedef std::shared_ptr<Expression> (Parser::*prefix_parser_fn)(void);
    ```

    - prefix_parser_fn函数是一个无参数，返回Expression指针的一个函数

  - 

  - ```
    typedef std::shared_ptr<Expression> (Parser::*infix_parser_fn)(const std::shared_ptr<Expression>&);
    ```

  - 定义在其他文件的函数

    - program.cpp

      - std::shared_ptr<Program> Parser::parse_program()
        - new一个Program对象
        - 只要m_curr的类型不为EOF，就不断地parse_statement()，并且会让上面定义的program对象不断地push_back这个statement

    - statement.cpp

      - std::shared_ptr<Statement> Parser::parse_statement()
        - return parse_expression_statement();
      - std::shared_ptr<Expression_Statement> Parser::parse_expression_statement()
        - new一个Expression_Statement对象
        - Expression_Statement里面只有一个Expression指针
        - 然后调用parse_expression(LOWEST)给m_expression
        - 

    - expression.cpp

      - std::shared_ptr<Expression> Parser::parse_expression(int precedence)
        - 这个函数是处理m_curr的方法
        - 首先在m_prefix_parser_fns里面找到m_curr类型的前缀回调函数
        - 如果没找到就报错，返回nullptr
        - 找到了就调用对应的前缀回调函数
          - 并且获得返回的Expression指针
        - 然后看下一个token对应的优先级是否大于当前的，如果大于，那么就要把当前解析的expression当作中缀表达式的左边部分传入到中缀回调函数里面

    - 回调函数

      - 前缀回调

        - ```
          {Token::TOKEN_INTEGER, &Parser::parse_integer},
          {Token::TOKEN_FLOAT, &Parser::parse_float},
          {Token::TOKEN_LPAREN, &Parser::parse_group},
          {Token::TOKEN_MINUS, &Parser::parse_prefix},
          {Token::TOKEN_TILDE, &Parser::parse_prefix},
          ```

        - 

      - 中缀回调

        - ```
          {Token::TOKEN_PLUS, &Parser::parse_infix},
          {Token::TOKEN_MINUS, &Parser::parse_infix},
          {Token::TOKEN_ASTERISK, &Parser::parse_infix},
          {Token::TOKEN_SLASH, &Parser::parse_infix},
          {Token::TOKEN_MODULO, &Parser::parse_infix},
          ```

- Object类

  - 

  - ```
    enum Type
    {
        OBJECT_ERROR = 0,
        OBJECT_INTEGER,
        OBJECT_FLOAT,
    };
    ```

  - 成员变量

    - Type m_type;
      - Object的类型
    - int64_t m_value;
      - 
    - static std::map<Type, string> m_names;
      - 类型对应的名字
    - std::shared_ptr<Object> Object::new_error(const char *format, ...)
      - new一个Error类
      - 按照格式写入错误信息
    - std::shared_ptr<Object> Object::new_integer(int64_t value)
    - std::shared_ptr<Object> Object::new_float(double value)
    - 


- evaluator文件夹
  - Evaluator类
    - bool Evaluator::is_error(const std::shared_ptr<Object> &obj)
      - 判断是否为error类型的node
    - std::shared_ptr<Object> Evaluator::new_error(const char * format, ...)
    - std::shared_ptr<Object> Object::new_integer(int64_t value)
    - std::shared_ptr<Object> Object::new_float(double value)
      - new一个object类型的值
    - std::shared_ptr<Object> Evaluator::cast_from_integer_to_float(const std::shared_ptr<Object> & obj)
      - 传入obj指针
      - 返回一个new_float
    - std::shared_ptr<Object> Evaluator::eval(const std::shared_ptr<ast::Node> &node)
      - 传入抽象解析树的节点
      - 查看这个节点的类型
        - NODE_PROGRAM
          - 调用eval_program
        - NODE_EXPRESSION_STATEMENT
          - 调用eval(m_statement)
        - NODE_INTEGER
          - 调用eval_integer
            - 直接返回m_value
        - NODE_FLOAT
          - 调用eval_float
            - 直接返回m_value
        - NODE_INFIX
          - 调用eval_infix
            - 先eval左边，再eval右边
            - 根据左边右边的数据类型来判断怎么计算
              - eval_integer_infix_expression
              - eval_float_infix_expression
            - 如果是不认识的数据类型或者左边右边eval出了error，就报错
        - NODE_PREFIX
          - std::shared_ptr<Object> Evaluator::eval_prefix(const std::shared_ptr< ast::Prefix> &node) 
            - 根据node的operation来处理
              - eval_minus_prefix_operator_expression
              - eval_tilde_prefix_operator_expression
                - 这两个函数都需要right是integer类型，否则报错
            - 如果有不认识的运算符，那就报错
        - 其他的就是错误了
          - 返回new_error
    - 定义在其他文件的函数
      - std::shared_ptr<Object> Evaluator::eval_program(const std::list< std::shared_ptr<ast::Statement >> &stmts) 
      - 传入Statement的list开始递归下降求值
      - 遍历Statement指针链表，一条一条地eval，并且赋值给result
      - 最后返回result
    - 



3b031fd

finish bit operator

位运算符 & |  ^ <<  >> 

```
1&2
1|2
3^4
1<<2
2>>1
```

lexer.cpp里面加入> | & ^ <

parser.cpp加入LOGIC运算符优先级，是最低的优先级

LOGIC

SUM

PRODUCT

PREFIX

还有这些位运算符的中缀回调函数

evaluator.cpp里面处理中缀ast的op增加几个操作



992b5fa

finish bool

```
true
false
```



ast增加一个node类型bool

evaluator文件夹

evaluator.cpp里面加一个new_bool

bool.cpp里的eval_bool

lexer.cpp里面增加一个is_letter，增加一个read_identifier函数，去读取标识符，和read_number一个思路

在default里面，也就是判断是否为数字的逻辑后面加一个is_letter，就去调用read_identifier，获得一个标识符，然后去查找这个标识符是不是关键字，来获得一个type

token里会增加一个成员变量m_keywords

```
std::map<string, Token::Type> Token::m_keywords = {
        {"true", TOKEN_TRUE},
        {"false", TOKEN_FALSE},
};
```

object增加bool值类型

parser里面增加parse_bool的前缀回调函数



98c4b9d

finish compare

```
1<2
1<2
1>2
1>=2
1!=2
1==2
```

evaluator里面增加< > <= >= == !=的逻辑，返回一个new_bool值

增加这几种token

lexer里面增加符号，这里是只需要加=

这里没办法识别<空格=

语法解析，增加中缀表达式的回调函数

增加一个COMPARE优先级

```
LOWEST = 0,
LOGIC,  //& | ^ << >>
COMPARE,
SUM,   // + -
PRODUCT, // *  /  %
PREFIX,
```



710ebce

finish logi

```
!true
false||true
true&&false
```

也就是与或非操作! && ||

token增加



evaluator增加对中缀表达式bool的操作，也就是左边为bool，右边为其他，怎么处理与或非

增加前缀表达式 !

与或的优先级是LOGIC

非的回调函数更新





3214ed8

finish string

```
'1ff\n'
"f\t\f\y"
```



token：增加对  ' 和  “  的识别



lexer：

read_single_quote_string单引号不转义，只会对单引号转义

双引号会转义，就是把对应的\n还是\t直接传到m_ch里面

ast：增加string类型的ast的node

evaluator:增加对string类型node的支持eval_string

也就是直接返回new_string(m->value)



finish string operator

500348d

```
3*'111'
"333"*5
```



增加了string+string，string*int的操作类型

同时增加了string和string之间的大小比较运算符



eb55668

finish null operator

```
null == null
null == 1

```



增加一个null值类型和关键字

eval_null

eval_diff_type_operator_expression就是根据运算符!=返回true，==返回false



```
std::map<string, Token::Type> Token::m_keywords = {
        {"true", TOKEN_TRUE},
        {"false", TOKEN_FALSE},
        {"null", TOKEN_NULL},
};
```

5be8951

finish variable init

```
name
age
```



ast增加一个node类型identifier，有一个string的成员变量

evaluator增加eval_identifier,现在还不会做处理

parser：增加parse_identifier直接new一个Identifier的语法树节点，然后把m_token和m_value塞进去就好了

lookup函数如果发现不是关键字，那么就返回TOKEN_IDENTIFIER类型







ffd9021

finish variable assign

```
name=5
age=6
```



ast增加assign类型的node节点，里面存储

std::shared_ptr<Expression> m_name;
std::shared_ptr<Expression> m_value;

一个是name表达式，一个是value表达式



evaluator：

增加Environment类

- 成员变量
  - std::map<string, std::shared_ptr<Object>> m_store;
    - 变量名对应的值
  - std::shared_ptr<Environment> m_outer;
    - 上一层Environment
  - void set(const string & name, const std::shared_ptr<Object> & value)
    - 给变量名字在环境变量里设置value
  - std::shared_ptr<Object> get(const string & name)
    - 获得这个变量的value，如果该变量里没有，就往m_outer里面找

eval_assign:把node->m_value给eval出来，再看node->m_name是不是标识符类型，如果是就在环境变量里面设置这个value就好了

repl里增加一个Environment env变量

在eval中传入env

eval_identifier会从env中查找变量名，看如果有的话直接返回值就好了

中缀回调函数

assign优先级

enum Precedence
            {
                LOWEST = 0,
                ASSIGN,  //=
                LOGIC,  //& | ^ << >>  && ||
                COMPARE,  // <=  >=  ==
                SUM,   // + -
                PRODUCT, // *  /  %
                PREFIX, // -a  ~a  !a   !a
            };

parse_assign：就是把左部传入，看左部是不是标识符，如果是就继续解析右边的expression



29ed386

finish compound operator

```
1+=2
2-=3
1*=3
2/=1
1<<=1
1>>=3
1^=1
1%=3
1&=1
1|=5
```

词法分析中增加对组合比如+=  -=   *=的支持

ast中增加compound类,和中缀类似，存储op左右

compound优先级也是assign

在evaluator中增加eval_compound

先解析左右，然后把op里面的除=之外的符号抽出来，就是infix的符号了，然后使用eval_infix就可以计算左op右的结果来更新标识符的值了



5c0ba00

finish postfix

```
a=0
b=1
a++
b--
a
```

ast增加后缀node类型，里面有一个op和m_left

parser里面需要在中缀

parse_expression里面在infix解析完后就增加postfix的逻辑

evaluator:

eval_postfix，递归下降解析postfix，解析left，然后看left是不是一个标识符，根据op来对标识符的值进行处理，把转变的值放到val里面，最后才变更到标识符里面，返回left的object

注意  后缀op的优先级是LOWEST，这样才不会进入infix的逻辑之中



f6fc0ea

finish ternary

```
a>b?1:2
a<b?1:2
```



三目运算符

ast增加ternary的node节点

三个成员变量

std::shared_ptr<Expression> m_condition;
std::shared_ptr<Expression> m_if_true;
std::shared_ptr<Expression> m_if_false;

condition条件语句，和两条跳转语句

eval_ternary的时候只需要判断m_condition然后去eval if_true或者if_false

词法分析lexer，增加对?和：的支持

parse增加ternary的优先级

```
enum Precedence
{
    LOWEST = 0,
    ASSIGN,  //=   += -= /=
    LOGIC,  //& | ^ << >>  && ||
    TERNARY,
    COMPARE,  // <=  >=  ==
    SUM,   // + -
    PRODUCT, // *  /  %
    PREFIX, // -a  ~a  !a   !a
};
```

遇到问号就parse_ternary

Parser::parse_ternary(const std::shared_ptr<Expression> &left)

left就是m_contition，然后解析if_true和if_false



8f8c32e

finish if

```
a=4
b=3
c=0
if a < b {
    c=100
}
else if a>b {
    c=200
}
else
{
    c=300
}
c
a
```

词法解析里面增加{}的token

增加if，else的token

parse里面增加了parse_block()

不断地调用parse_statement然后插入到block的m_statements里面，最后监测} 的出现

parse_if函数：把if的m_condition读入，监测{ 的出现，然后parse_block()，这时候m_curr是},然后监测m_peek是不是else，如果是就执行两次next_token函数，这样m_curr就是if或者是{分别对应else if和else{，然后分别保存为senario就好了，如果是else {的情况，它的m_condition就设为true即可，因为是list里面最后一个的scenario



ast增加block的node类型

std::list< std::shared_ptr<Statement> > m_statements;

成员变量是一系列的Statement



if.h里面

ast增加Scenario的node类型

但是类叫做Scenario

成员变量有std::shared_ptr<Expression> m_condition;存储条件表达式

std::shared_ptr<Block> m_body;存储语句块

ast增加if的node类型

成员变量std::list< std::shared_ptr<Scenario> > m_scenarios;

包含了一系列的scenarios

意味着if else if …… else的嵌套的多场景（译为脚本）

evaluator：

eval_block函数：遍历block类型的node里面的m_statements，一句一句地eval，最后return一个new_null

eval_if函数：遍历所有的scenarios，如果发现某个scenario的condition是true，那就eval那个scenario的m_body



74ffaef

finish while

```
i = 0
s=0
while i<5 {
    i++
    if i % 2 == 0 {
        continue
    }

    s++
}
s
```



ast增加break、continue、while的node类型

Break类是继承Statement的，不同于其他的继承自Expression，它没有成员变量

Continue类也是继承Statement的

While类继承自Expression，成员变量是std::shared_ptr<Expression> m_condition;条件语句
std::shared_ptr<Block> m_body;执行语句

增加break，continue的object类型，

在词法分析中看到break或者continue的token之后，就会生成对应的ast节点node，然后语法解析parser的时候，看到对应的break和continue节点就会变成object，object有一个str方法可以查看它的名字是什么

evaluator:在求值过程中

eval_block遇到了break和continue语句的时候，会直接返回这个eval出来的break Object或者continue

eval_if也是一样的，如果senario的condition为true，就要执行m_body也就是eval_block，如果发现返回来的是一个break或者continue，也继续return出去（为的是让上层的for或者while接收到）

eval_while逻辑：先eval 一下condition，进入while(contition)然后eval(body)，看eval出来的是否有错误，是否是break，是break就直接break出循环，continue和继续下一轮循环的逻辑是一样的，不需要特殊处理，继续计算更新condition的值即可



685c173

finish for

```
sum = 0
for i = 0; i < 10; i += 2{
    sum ++
}
sum
```

token增加分号；

parse_for函数去解析for的结构





ast增加for的node类型，成员变量有四个

std::shared_ptr<Expression> m_starter;开始语句
std::shared_ptr<Expression> m_condition;条件语句
std::shared_ptr<Expression> m_closer;步进语句
std::shared_ptr<Block> m_body;



evaluator：

先执行start，再在死循环中计算condition，如果为false就break死循环，然后执行body，如果eval出来是break，那就break，否则执行closer步进语句，如此循环



bce11e8

finish switch,todo finish break

```
a = 0
name = null
switch a {
    default:
        name = 'sean'
    case 1:
        name = 'jack'
    case 2:
        name = 'lucy'
    case 3, 4:
        name = 'lily'
        break
}
name
```

token增加了一个逗号的token，为了方便case 3,4

增加了default，switch，case的token



parse_switch函数

先读取m_value，然后开始读取case，一个case至少有一个value，m_values存储多个value，先push_back一个，然后看有没有逗号token再push_back一个，最后如果发现了default的token就让m_default为true

然后是冒号，读取后面的body，知道读取到case或者default就停下



ast增加case、switch的node类型

case成员变量

std::list< std::shared_ptr<Expression>> m_values;case的值

std::shared_ptr<Block> m_body; case所要执行的语句
bool m_default = false;  是否为default部分

Switch成员变量

std::shared_ptr<Expression> m_value; switch所带的语句表达式
std::list< std::shared_ptr<Case> > m_cases;一系列的case

目前关键字

```
std::map<string, Token::Type> Token::m_keywords = {
        {"continue", TOKEN_CONTINUE},
        {"break", TOKEN_BREAK},
        {"for", TOKEN_FOR},
        {"switch", TOKEN_SWITCH},
        {"case", TOKEN_CASE},
        {"default", TOKEN_DEFAULT},
};
```

evaluator

先eval出m_value

去遍历m_cases，如果一个case的m_values里面有一个value和m_value是一致的，就执行body，并且记录下标记f，接下来的case不需要再判断是否和m_value 一致，都一概执行，除非遇到break，最后如果没有进入任何一个case，就要执行default里面和以下的case

77bd83c

finish list

```
name="1234"
[1,1+2,name,true]
```

增加[]两种token

parse_expression_list和parse_list去parse list类型

ast：增加list的node节点，成员变量

std::vector< std::shared_ptr<Expression> > m_elements;

list里面就是一系列的expression指针



evaluator

eval_list就是一个一个地eval list的ast的m_elements的元素，然后存储到object类型的List里面的m_elements



e2cda08

finish index visit

```
name="1234"
list = [1,2,3]
list[-2]
```



索引是属于中缀表达式，使用[触发，调用parse_index作为回调

ast：增加index的node类型

成员变量 

std::shared_ptr<Expression> m_left;list名字
std::shared_ptr<Expression> m_index;索引的表达式

evaluator

eval_index_expression

先eval left和index，然后去匹配对应的类型调用对应函数即可

目前的优先级

```
enum Precedence
{
    LOWEST = 0,
    ASSIGN,  //=   += -= /=
    LOGIC,  //& | ^ << >>  && ||
    TERNARY,
    COMPARE,  // <=  >=  ==
    SUM,   // + -
    PRODUCT, // *  /  %
    PREFIX, // -a  ~a  !a   !a
    INDEX,
};
```



9ae26d2

finish index assignment

```
name="1234"
list = [1,2,3]
list[2] ++
list
```



evaluator:

复用eval_assign，

assign的成员有m_name和m_value

之前是m_name的类型是标识符，现在加一个index

如果是index，就调用eval_index_assignment

然后在调用eval_list_index_assignment来操作list类型的index的eval

可以把握怎么调用index，比如index为负数，index超过vector最大容量



468bc0d

finish list add and multiply

在eval_infix的时候增加对list * int和list + list的支持



cc8896b

finish string index

```
"111"[0]
"kitty"[-2]
```

增加一个eval_string_index_expression的函数

在eval_index_expression里面增加string[index]这样的支持



8ca96d3

finish hash hashable and string hashable

```
{"1":2, "2":4}
```



ast增加hash的node类型，一个成员函数

std::map< std::shared_ptr<Expression>, std::shared_ptr<Expression>> m_pairs;

(可以换成vector<pair<>>)

一个表达式对应另一个表达式的map，其实是key，value表达式

parse_hash函数，肯定是遇见了{类型的token触发的，然后就是去识别key的expression，然以冒号，然后是value的expression，



object的一个独立文件：hashable.h

有HashKey类，成员变量

Object::Type m_type;该hashkey的object类型
string m_value;

也有各种比较运算符的重载，就是比较这个m_value的大小

也就是说我们会把key统一转换成一个string类型，然后塞进map里面比较

有Hashable接口类，只有一个virtual HashKey hash() = 0;虚函数





hash相关的object类型：

HashPair，成员变量

std::shared_ptr<Object> m_key;
std::shared_ptr<Object> m_value;

Hash，成员变量

std::map<HashKey, HashPair> m_pairs;



evaluator:

eval_hash函数，参数是hash的ast，遍历m_pairs获得key和value的eval出来的object类型，然后对key的object类型进行Hashable的强制转换，最后定义一个Hashpair把key和value的object类型塞进去，然后Hash类型的m_pair的key值是一个hashable->hash()，也就是HashKey



给Object::String类加上一个Hashable的继承，重写hash函数，让m_type和m_value填充上即可





0cb695c

finish hashable

```
{true : 3, 1:2, 2.13:3}
```

在object类型中对bool、int、float、null增加hashable的接口支持，

使用hash<string> hash_func来计算对应数据类型的string的hash值

```
virtual HashKey hash()
{
    std::hash<string> hash_func;
    auto hash_code = hash_func(std::to_string(m_value));
    HashKey h;
    h.m_type = type();
    h.m_value = hash_code;
    return h;
}
```

目前关键字

```
std::map<string, Token::Type> Token::m_keywords = {
        {"true", TOKEN_TRUE},
        {"false", TOKEN_FALSE},
        {"null", TOKEN_NULL},
        {"if", TOKEN_IF},
        {"else", TOKEN_ELSE},
        {"while", TOKEN_WHILE},
        {"continue", TOKEN_CONTINUE},
        {"break", TOKEN_BREAK},
        {"for", TOKEN_FOR},
        {"switch", TOKEN_SWITCH},
        {"case", TOKEN_CASE},
        {"default", TOKEN_DEFAULT},

};
```



3ba6fdd

finish hash visit

```
hash={true : 3, 1:2, 2.13:3}
hash[2.13]
```

增加eval_hash_index_expression的逻辑



7bf8c5e

finish hash assignment

```
hash={true : 3, 1:2, 2.13:3}
hash[2.13]=4
hash[2.13]--
hash[2.13]
```

在assign的eval逻辑中增加eval_hash_index_assignment



1c77fed

finish property visit

```
hash = {'name': 'jack', 'age': 18}

hash.name
hash.age

```

增加.token

作为一个中缀表达式解析property，以dot token触发

//（这里有bug，比如hash.1是会把1在语法解析的时候解析成一个identifier，这并不对）

ast里增加NODE_PROPERTY的node类型

成员变量

std::shared_ptr<Expression> m_object; 属性的主题，比如hash表
std::shared_ptr<Expression> m_property;属性

eval_property_expression

先把m_object给eval出来，然后检查m_property的type是不是identifier，然后转换成String类作为index。然后如果m_object是hash值，那么调用eval_hash_index_expression，这个函数以前实现过



837808d

finish property assignment

```
hash = {'name': 'jack', age: 18}

hash.name = 'lucy'
hash.age += 2
hash.height = 170
hash
```

优先级

```
enum Precedence
{
    LOWEST = 0,
    ASSIGN,     // =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
    IN,         // in
    LOGIC,      // &, |, ^, &&, ||, <<, >>
    TERNARY,    // ?
    COMPARE,    // >, >=, <, <=, ==, !=
    SUM,        // +, -
    PRODUCT,    // *, /
    PREFIX,     // -a, ~a, !a
    CALL,       // function(x)
    INDEX,      // list[index]
    DOT,        // object.property or object.function()
};
```

assign的优先级是很低的，所以property能够作为assign的左边

eval_property_assignment

修改传入的property的具体index对应的value就好了



49e0806

finish in operator

```
4 in [1, 2, 3]
```



ast增加in的node类型

作为一个中缀表达式，回调函数是parse_in

std::shared_ptr<Expression> m_left; in左边
std::shared_ptr<Expression> m_right; in右边

然后在evaluator上面增加

eval_in

eval_in_string，首先左边类型得是string，然后看右边string有没有一致的

eval_in_list，看左边的类型和值在list里有没有一致的

eval_in_hash的函数

最后返回一个Bool类型的object



bb53669

finish function return eval

```
sum = fn(x, y) {
    return x + y
}
total = sum(1,2)
```

增加return和function的token

parse_return直接解析一个return后面的语句即可

parse_function先解析左括号里面的参数列表，然后解析body





ast增加Function、return的node类型

Function成员函数

std::vector< std::shared_ptr<Identifier>> m_parameters; 参数列表
std::shared_ptr<Block> m_body;函数体

Return成员函数

std::shared_ptr<Expression> m_value;一个return

的表达式



object类型增加return和function

function成员函数

std::vector< std::shared_ptr<Identifier> > m_parameters;和ast的一样

std::shared_ptr<Block> m_body;和ast的一样
Environment * m_env = nullptr;在eval的时候会new一个，作为局部变量的environment

return的成员变量

std::shared_ptr<Object> m_value;就是一个eval过后的return语句



现在还没实现call函数调用



72bc135

finish function call

```
sum = fn(x, y) {
    return x + y
}
total = sum(1+2,3*8)
total
```



ast增加call的node类型

std::shared_ptr<Expression> m_function; 函数的表达式
std::vector< std::shared_ptr<Expression> > m_arguments; 参数的表达式列表



block在eval的时候遇到return会直接return这个类型的object，

在eval_call里面会先eval function和参数列表（这个需要遍历然后插入），接着调用apply_function(obj, args);，把结果计算出来然后return

apply_function要先调用extend_function_env(func, args)把func里面的参数和args里面的参数一一对应，并且给func里面的m_env对应的args的变量赋值

之后就可以eval 函数的body了，使用func自己的m_env就好了。如果接收到return类型的obj，那么就直接返回这个obj就好了，调用函数就结束了



143feef

finish function call scope recursion

```
foo = fn(a) {
    if a == 0 || a == 1{
        return a
    }
    return foo(a-1) + foo(a-2)
}
foo(5)

```

在eval_function的时候，env环境指针是函数原来作用域的

eval_call的时候，会把函数原来作用域当作outer，以new Environment(fn->m_env)的形式定义一个新的作用域

修改了extend_function_env的逻辑，使其生成新的作用域



1fc341a

finish environment and closure bugs

```
f = fn(x) {
    return fn(y) {
        return x + y
    }
}

f1 = f(2)
f1(5)
```

environment类新增一个成员变量

std::vector<Environment *> m_inner;

用来记录当前作用域的子作用域，用在析构函数上



041f5ce

finish function default params

```
f = fn(x, y=2) {
    return y
}
f(4)
```

需要在function的node类型增加一个成员变量

std::map<string, std::shared_ptr<Expression>> m_defaults;

就存储有默认参数的参数表达式

然后在evaluator的call逻辑就可以先读取defaults的参数了

默认参数必须定义在后面，如果在前面有定义默认参数，后面没定义的话，在parse_function的时候会直接报错

具体逻辑是，如果触发了= token，那就往m_default里面插入元素，之后如果没有触发= token，就要判断m_default是否为空，不为空的话就要报错



73c6b3a

finsh token info

完善token的报错机制



ebf4c1d

finish return single

```
add = fn(x, y) {
    return x + y
}
a=3
foo = fn() {
    a = 1
    return
}
foo()
a
```

parse_return会增加逻辑，如果m_curr和m_peek的行数不同，return的ast节点的m_value就会当作是一个null语句



f159663

finish builtin function print

```
list = [1,2,4]
print(1,2,1+4, list)
```

内置函数不会在词法分析上有什么区别，都是识别为identifier

然后会作为函数在函数调用中被查找到

object增加Builtin的类型

成员变量

string m_name;
static std::map<string, method> m_methods;



在evaluator/identifier.cpp里面，如果没有在环境指针中寻找到值，那就调用Bulition::find函数在m_methods里面寻找内置函数是否存在，并且返回内置函数的object类型也就是Builtin类型

在object/builtin.cpp函数里面会写内嵌函数的逻辑

然后evaluator里面的eval_call里面增加OBJECT_BUILTIN逻辑，和函数一样，准备好参数的具体值。然后调用apply_function就好了

print内置函数的逻辑是，遍历参数列表，把每个object类型的str函数给输出就好了



dd592a3

a64d321

finish type builtin

```
type(123)

```

增加的内置函数

 ```
std::map<string, Builtin::method> Builtin::m_methods = {
        {"print", &Builtin::_print},
        {"type", &Builtin::_type},
        {"len", &Builtin::_len},
        {"int", &Builtin::_int},
        {"float", &Builtin::_float},
        {"str", &Builtin::_str},
        {"exit", &Builtin::_exit},
};
 ```

type函数的逻辑，：检查参数个数，然后把参数的第一个获取，返回它的name函数就好了

exit的逻辑：直接调用::exit，值就设为传入的参数

























//



```
std::shared_ptr<Object> Evaluator::eval_switch(const std::shared_ptr<ast::Switch> &node,
                                               pi::evaluator::Environment *env) {
    auto obj = eval(node->m_value, env);
    if (is_error(obj))
    {
        return obj;
    }
    bool f = false;
    bool f_all = false;
    for (auto & opt : node->m_cases)
    {
//        if (opt->m_default) std::cout << "?" << std::endl;
        if (opt->m_default)
        {
            if (f) eval_block(opt->m_body, env);
            continue;
        }
        for (auto & exp : opt->m_values)
        {
            auto res = eval(exp, env);
            if (f || (obj->type() == res->type() && obj->str() == res->str()))
            {
//                std::cout << f << std::endl;
                f = true;
                auto e = eval_block(opt->m_body, env);
                if (e->type() == Object::OBJECT_BREAK)
                {
                    f_all = true;
                }
                break;
            }
        }
        if (f_all) break;
    }
    if (f) return new_null();

    for (auto & opt : node->m_cases)
    {
        if (f || opt->m_default)
        {
            f = true;
            auto e = eval_block(opt->m_body, env);
            if (e->type() == Object::OBJECT_BREAK)
            {
                break;
            }
        }
    }
    return new_null();
}
```







```
add = fn(x, y) {
    return x + y
}

foo = fn(a,b) {
    a = 1
    b = 2
    return
}
a=4
foo(1,2)

a
```

存在bug，解决方案

evaluator/assign.cpp的

```
case Node::NODE_IDENTIFIER:
{
    auto e = std::dynamic_pointer_cast<ast::Identifier>(node->m_name);
    env->set(e->m_value, obj);
    return new_null();
}
```

这里的env->set，如果m_value不在本作用域，查找上面的作用域是否存在，如果存在就在那里修改（目前看来就不太行的），看来这不是一个bug

在python里面就是这样处理的





