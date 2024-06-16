用户手册

源文件是code.pi

运行my_interpret,可以看到源文件的所有token，并且更新token.json

运行ast，可以看见源文件的抽象语法树ast，并且更新ast.json

运行eval，可以获得源文件的运行结果

运行eval_repl，可以进入repl模式

example文件夹中有实例程序



该语言支持整形，浮点型，布尔型，字典（支持整形、字符型、null、浮点型作为key），列表（可存储不同数据类型）

```
list = ['jack', 'lucy', 'lily', 2]
list[0] += 'sean'
list[1] *= 10
list[3] ++
list[2] += list[0]
print(list)


// 字符串
print('kk' in 'kitty')

// 列表
print(4 in [1, 2, 3])

// 字典
print('name' in {'name': 'jack', 'age': 18})
```



```
hash = {'name': 'jack', 'age': 18}
a = {123 : 'abc', true: 'kitty', null: 456, 'name': 'jack'} // 可哈希的类型有，整形，bool型，null型，字符串型
// 可直接对属性赋值，可直接使用.运算符操作属性
hash.name = 'lucy'
hash.age += 2
hash.height = 170

print(hash)

// 可以使用索引访问
hash = {'name': 'jack', 'age': 18}
print(hash['name'])
print(hash['age'])

// 使用in运算符
print('name' in hash)
```

支持控制流 if，while，for，switch

```
a = 1
b = 1

if a < b {
    c = 'less than'
} else if a > b {
    c = 'great than'
} else {
    c = 'equal'
}
print(c)

i = 0
sum = 0
while i < 10 {
    sum += i
    i++
}
print(sum)


sum = 0
for i = 0; i < 10; i++ {
    sum += i
}
print(sum)

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

支持函数、闭包、高阶函数

```
add = fn(x, y) {
    return x + y
}

foo = fn() {
    a = 1
    b = 2
	print('foo running')
    return
}

print(add(1, 2))
foo()

```

```
f = fn(x) {
    return fn(y) {
        return x + y
    }
}

f1 = f(2)
f1(3)
```



```
add = fn(x, y) {
    return x + y
}

sub = fn(x, y) {
    return x - y
}

foo = fn(x, y, f) {
    return f(x, y)
}

print(foo(5, 3, add))
print(foo(5, 3, sub))

```

支持内置函数

print、type、len、int、float、str、exit

支持列表和字典的内置函数

列表.append    .len

字典.len   .get







