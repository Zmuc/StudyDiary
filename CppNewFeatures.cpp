/* ——————————————————————————————————————————————————
 * C++ 11 新特性 */

1. 基于范围的循环
用法： for (变量 : 范围) { }
基于循环执行容器vec中的所有数据。
例如：
	vector<int> vec;
	for (int i : vec) {
		...
	}

2. nullptr
nullptr为了替代NULL，类型为nullptr_t，用来区分空指针和0。

3. 类型推导
1）auto只能对变量进行类型推导，不能用于推导数组类型，也不能用于函数传参（传参考虑用模板来进行函数重载）。
例如：
	// cbegin()返回的数据类型为vector<int>::const_iterator，可用auto推导
	for(auto itr = vec.cbegin(); itr != vec.cend(); ++itr)
2）decltype是类型说明符，用于解决复杂的类型声明，不会实际计算表达式的值，而是分析表达式并得到它的类型。decltype可以作用于变量、表达式及函数名。
例如：
	using FuncType = int(int &, int);
	int func(int &p1, int p2);
	// decltype(func) <-> FuncType
	decltype(func) *pfunc = func;
3）拖尾返回类型，使用auto推导函数的返回类型。
例如：
	template<typename P, typename X>;
	auto func(P p1, X p2) -> decltype(p1 + p2) {
		return p1 + p2;
	}

4. 初始化列表
提供统一的语法来初始化任意的对象，还允许构造函数或其他函数像参数一样使用初始化列表（通过std::initializer_list）。
例如：
	#include <initializer_list>

	struct Xs {
		int a;
		float b;
	};

	class  Xc {
	public:
		Xc(std::initializer_list<int> list) {}
	};

	Xs s {1, 2.3};
	Xc c = {1, 2, 3};

5. 模板增强
1）
