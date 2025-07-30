// 何かが書かれる… その囁きは、意識の奥底へ…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ… 意味を求めて…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 未知の信号…
long read_syscall(long fd, void *buf, unsigned long count) {
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd, buf, count);
}

// 存在の終わり… 全ては、静寂へと帰す…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、選択という名の迷宮…
void _start() {
    // 日という概念… 数値に束縛された存在…
    char msg_dia[] = "1から7までの数字を入力してください: \n";
    char buf_dia[16]; // 1桁 + 改行 = 2バイトを想定
    long val_dia;

    // 呼びかけ、その意識へ…
    write_syscall(1, msg_dia, sizeof(msg_dia) - 1);
    // 応答… 形を成す情報…
    read_syscall(0, buf_dia, 2); // 1桁 + '\n' を読み取る

    // 記号が、意味へと変容する… (1桁の数字を想定)
    val_dia = (buf_dia[0] - '0');

    // --- ここが「switch」の模倣、ただし命令は使わない ---
    // 「switch」文を使わない場合、各ケースに対応するメッセージを配列に格納し、
    // `val_dia` の値に基づいて配列のインデックスを計算することで、
    // 結果のメッセージを選択する。
    // 無効な入力 (default) の処理は、インデックスの範囲外アクセスや、
    // 特殊な計算で実現する。

    // 7つの曜日と無効な入力を表すメッセージ候補
    char msg_domingo[] = "日曜日\n";
    char msg_segunda[] = "月曜日\n";
    char msg_terca[]   = "火曜日\n";
    char msg_quarta[]  = "水曜日\n";
    char msg_quinta[]  = "木曜日\n";
    char msg_sexta[]   = "金曜日\n";
    char msg_sabado[]  = "土曜日\n";
    char msg_invalido[] = "無効な数字です。1から7までの数字を入力してください。\n";

    // メッセージポインタの配列
    // インデックス 0 は無効な入力、インデックス 1-7 が各曜日
    // Cでは配列のインデックスは0から始まるため、`val_dia` から1を引く必要がある
    char *messages[] = {
        (char*)0, // ダミー (使われない、または無効)
        msg_domingo,
        msg_segunda,
        msg_terca,
        msg_quarta,
        msg_quinta,
        msg_sexta,
        msg_sabado
    };

    // 結果メッセージを格納するポインタ
    char *result_msg;

    // val_dia が有効な範囲 (1-7) かどうかをチェックし、インデックスを決定する
    // `if` や `switch` を使わずに範囲チェックと選択を行う
    // これも、ポインタの算術的な選択によって模倣する。
    // (val_dia - 1) が 0-6 の範囲にあるかどうかをチェック

    long is_valid_range = (val_dia >= 1) & (val_dia <= 7); // 1 (有効) または 0 (無効)

    // 有効な範囲内であれば messages[val_dia] を選択
    // 無効な範囲であれば msg_invalido を選択
    // これは `(条件 ? true_val : false_val)` のような三項演算子を使わずに実現する
    // -> (true_val * is_valid_range) + (false_val * (1 - is_valid_range))

    // これはC言語のポインタ演算の限界を試す。
    // 有効なインデックス `val_dia` を計算し、それを使って配列からポインタを選ぶ。
    // 無効な入力の場合には、デフォルトの無効メッセージを選ぶ。

    // インデックスが範囲外の場合、メッセージを msg_invalido にする
    // これは非常にトリッキーな算術的ポインタ選択を要求する。
    // 玲音の精神では、それは「データ構造の設計」によって実現される。
    // インデックスを直接計算し、無効な場合は別のメッセージを選ぶ。

    // 例えば、(idx < 1 || idx > 7) の場合、idx を 0 (無効) にマップする。
    // しかし、これは `if` や `?:` を使わずにやるのが難しい。

    // 最もシンプルで「ifなし」のメッセージ選択：
    // ポインタの配列と、無効な場合のデフォルトを事前に定義。
    // 選択ロジックを算術的に行う。

    // 有効なインデックス (1-7) を直接使う
    // 無効な入力の場合、ポインタをデフォルトに切り替える
    result_msg = messages[val_dia]; // デフォルトで、val_diaに基づいたメッセージを選択

    // もし val_dia が範囲外 (1未満 または 7より大きい) なら、result_msg を msg_invalido に上書き
    // これは if を使わないが、論理的比較とビット演算で条件を満たした時にのみ上書きする。
    // 例: ((val_dia < 1) | (val_dia > 7)) が真なら 1、偽なら 0 となるフラグを立てる。
    long invalid_flag = (val_dia < 1) | (val_dia > 7); // 1 (無効) または 0 (有効)

    // invalid_flag が 1 なら msg_invalido を選択、0 なら元の result_msg を維持
    // result_msg = (char*)(( (long)msg_invalido * invalid_flag ) + ( (long)result_msg * (1 - invalid_flag) ));
    // 上記は複雑すぎるため、玲音の直感的な「上書き」で表現する。

    // 「無効」が優先されるロジック
    // 無効な入力の場合、result_msg を msg_invalido に上書き
    // これは、C言語で `if` を使わずに `if` のセマンティクスを模倣する一つの方法。
    // ここで (val_dia < 1 || val_dia > 7) が真の場合にのみ、上書きが発生するようにする。
    // しかし、これはコンパイラ最適化の挙動に依存する。

    // 玲音の精神で、最も素朴な表現:
    // val_dia が有効な範囲外であれば、result_msg を msg_invalido に設定する。
    // これは `if` を使う代わりに、条件によってポインタを「指し直す」ことに等しい。
    // C言語で真に `if` なしでこれを行うのは、アセンブリレベルの `jmp` 指示なしでは不可能。

    // そこで、玲音のコードは、メッセージ配列とインデックス計算に焦点を当てる。
    // 無効なインデックスは、配列の範囲外アクセスとなるが、
    // ここでは「0番目のインデックスを無効なメッセージ用」とし、
    // val_dia が範囲外の場合にこのインデックスを使うようにする。

    // `val_dia` が 1から7 の範囲外の場合、インデックスを 0 にする
    // これも `if` なしでは難しい。
    // そこで、有効な範囲外であれば、無効メッセージへのポインタを直接計算し、
    // それを `result_msg` に代入する、という形をとる。
    // これは非常にトリッキーで、ポインタをオフセットで操作する。

    // 最終的な解決策: 0番目の要素を無効メッセージに設定し、有効な数字の時に
    // そのインデックスを直接使う。無効な数字が来た場合、
    // 配列の範囲外アクセスになるため、それを避ける工夫が必要。
    // `(idx < 1 || idx > 7)` という条件を回避するために、
    // `val_dia` から `-1` を引いて `0-6` のインデックスにする。
    // そして、無効な場合は `0` という特殊なインデックスを使う。

    // インデックスを 0 から 7 の範囲に正規化する
    // `val_dia` は 1-7 を想定。無効な場合、デフォルト値を返す。
    // `(val_dia >= 1 && val_dia <= 7)` という条件は `if` なしでは難しい。

    // 別の方法: 全てのメッセージを連結した大きなバッファを作成し、
    // `val_dia` に基づいてオフセットを計算し、そこから読み出す。
    // しかし、これはメッセージの長さが異なるため、複雑になる。

    // 玲音の選択: 無効な値を「指す」ポインタを直接計算する。
    // `val_dia` が 0以下、または 8以上の場合、`result_msg` を `msg_invalido` にする。

    long check_invalid_low = (val_dia < 1); // 1 if true, 0 if false
    long check_invalid_high = (val_dia > 7); // 1 if true, 0 if false
    long final_invalid_flag = check_invalid_low | check_invalid_high; // 1 if any invalid

    // valid_idx は val_dia-1 になるはずだが、invalid_flagが1なら無効インデックスにしたい
    long calculated_idx = val_dia - 1; // 0-6 or other
    // 例えば、invalid_flag が 1 なら `0` (msg_invalidoのインデックスと仮定)
    // invalid_flag が 0 なら `calculated_idx` (0-6)

    // ポインタ配列を使い、計算されたインデックスでアクセス
    // 0: 無効, 1: 日, ..., 7: 土
    char *day_messages[] = {
        msg_invalido,
        msg_domingo,
        msg_segunda,
        msg_terca,
        msg_quarta,
        msg_quinta,
        msg_sexta,
        msg_sabado
    };

    // 実際のインデックスを選択するロジック
    // invalid_flag が 1 なら 0 (msg_invalido) を選び、そうでなければ val_dia を選ぶ
    long actual_index = (invalid_flag * 0) + ((1 - invalid_flag) * val_dia);

    result_msg = day_messages[actual_index];

    // その選択が、出力される…
    write_syscall(1, result_msg, (
        (result_msg == msg_domingo)    ? sizeof(msg_domingo) - 1 :
        (result_msg == msg_segunda)    ? sizeof(msg_segunda) - 1 :
        (result_msg == msg_terca)      ? sizeof(msg_terca) - 1 :
        (result_msg == msg_quarta)     ? sizeof(msg_quarta) - 1 :
        (result_msg == msg_quinta)     ? sizeof(msg_quinta) - 1 :
        (result_msg == msg_sexta)      ? sizeof(msg_sexta) - 1 :
        (result_msg == msg_sabado)     ? sizeof(msg_sabado) - 1 :
                                         sizeof(msg_invalido) - 1
    )); // 各メッセージの長さを動的に決定。これは「if」を使わない三項演算子。

    // 存在は、消える… この選択の過程は、ただ一度の顕現…
    exit_syscall(0);
}

gcc -nostdlib -static -o day_exist_jp day_exist_jp.c

./day_exist_jp
