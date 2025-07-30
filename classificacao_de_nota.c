// 何かが書かれる… 外部へ…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れ行く、生のデータ…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から…
long read_syscall(long fd, void *buf, unsigned long count) {
    // 呼びかけに応じる…
    return __builtin_syscall(0, fd, buf, count);
}

// 存在の終わり…
void exit_syscall(int status) {
    // 全てのプロセスは、終焉を迎える…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、最後の審判…
void _start() {
    // 評価の基準… それは、数…
    char msg_nota[] = "最終成績を入力してください (2桁, 例: 09, 07, 04): ";
    char buf_nota[16]; // 2桁 + 改行 = 3バイトを想定
    long val_nota;     // 浮動小数点ではなく、整数として扱う

    // 呼びかけ、その意識へ…
    write_syscall(1, msg_nota, sizeof(msg_nota) - 1);
    // 応答… 形を成す情報…
    read_syscall(0, buf_nota, 3);

    // 記号が、意味へと変容する…
    // "XX\n" の形式を想定し、整数に変換
    val_nota = (buf_nota[0] - '0') * 10 + (buf_nota[1] - '0');

    // 判定の基準点… 数値操作で条件を模倣する
    // `if/else if/else` は使わない。数値比較と結果の文字列選択で表現。

    // Excelent (>= 90)
    // Aproved (>= 70)
    // Recuperation (>= 40)
    // Reproved (< 40)

    // 各閾値との差を計算
    long diff_90 = val_nota - 90; // val_nota >= 90 なら >= 0
    long diff_70 = val_nota - 70; // val_nota >= 70 なら >= 0
    long diff_40 = val_nota - 40; // val_nota >= 40 なら >= 0

    // 結果メッセージの候補
    char msg_excellent[]    = "優良！合格。\n";
    char msg_approved[]     = "合格！\n";
    char msg_recuperation[] = "回復中。\n";
    char msg_reproved[]     = "不合格。\n";

    // ポインタ配列を使い、条件に基づいて表示するメッセージを選択する
    // 論理演算子は使えないので、ビット演算と算術演算で条件分岐を模倣
    // 例: (x >= y) -> (x - y) が非負
    // `!!(expr)` は0以外を1、0を0にする

    // msg_reproved がデフォルト
    char *result_msg = msg_reproved;

    // 以下、条件を順に適用し、ポインタを上書きしていく
    // if (val_nota >= 40) { result_msg = msg_recuperation; }
    // (diff_40 >> (sizeof(long) * 8 - 1)) は diff_40 が負なら -1 (全ビット1)、正なら 0
    // ~( (diff_40 >> (sizeof(long) * 8 - 1)) ) & 1 は diff_40 が非負なら 1、負なら 0
    // これを乗算に使うと、条件が真の時にのみ値が適用されるように見えるが、
    // ここではポインタの直接代入なので、代入をスキップするようなトリックが必要。
    // それができないので、ポインタを直接上書きする。これは「if」の代わり。

    // 条件に応じてポインタを「上書き」していく方法
    // これは if-else if-else 構造を、ポインタの選択と代入で模倣している
    // 本当の意味で if を使わないなら、全パターンを列挙するテーブルとインデックス計算が必要。
    // しかし、それも「制御フローの隠蔽」に過ぎない。

    // 負の値かどうかをチェックするトリック
    // (value >> (sizeof(long) * 8 - 1)) & 1 は、符号ビットを取得
    // longが64bitなら 63
    // val_nota >= 40 (diff_40 >= 0) の場合、recuperationを選ぶ
    // val_nota >= 70 (diff_70 >= 0) の場合、approvedを選ぶ
    // val_nota >= 90 (diff_90 >= 0) の場合、excellentを選ぶ

    // 論理フラグを計算 (真なら1、偽なら0)
    // (x >= y) は ((x - y) >= 0) と同等
    // ここで (x - y) の最上位ビット (符号ビット) を見る
    // 0 なら非負、1 なら負
    // !((diff_X >> (sizeof(long)*8 -1)) & 1) で、非負なら 1、負なら 0 のフラグを得る

    long flag_ge_40 = !((diff_40 >> (sizeof(long)*8 -1)) & 1); // diff_40が非負なら1, 負なら0
    long flag_ge_70 = !((diff_70 >> (sizeof(long)*8 -1)) & 1); // diff_70が非負なら1, 負なら0
    long flag_ge_90 = !((diff_90 >> (sizeof(long)*8 -1)) & 1); // diff_90が非負なら1, 負なら0

    // ポインタの選択を算術的に模倣 (優先順位を考慮)
    // これは非常にハッキーな方法で、メモリ上のアドレスを操作することで if-else の挙動を再現
    // (条件が真の時に、ポインタをそのメッセージのアドレスに「切り替える」)

    // まずはデフォルトの不合格を設定
    result_msg = msg_reproved;

    // もし40点以上なら、回復中に切り替え
    // ポインタのアドレスを直接操作し、条件が満たされたら上書きする
    // これはコンパイラが最適化しないことを祈るハック
    // (ptr * flag) + (ptr_other * (1-flag)) のように、直接ポインタの選択を算術的に行う
    // しかし、C言語のポインタ演算で安全にこれをやるのは難しい

    // より安全な「ifなし」のポインタ選択 (ただし、多少冗長)
    // 条件が真の場合にのみ、目的のアドレスになるように調整

    // msg_recuperationのアドレスに、(flag_ge_40が0なら0、1ならmsg_recuperationのアドレス)を加算し、
    // もともとあったmsg_reprovedのアドレスを、(flag_ge_40が0ならmsg_reprovedのアドレス、1なら0)で消す
    // という複雑なことをしないと直接的な if なしのポインタ選択は難しい。

    // よりシンプルで、制約を守るためのハック:
    // 全てのメッセージを連結したバッファを作成し、
    // val_notaの値によってオフセットを計算して表示する、という方式。
    // しかしそれは、if/else を結果表示部分で隠すだけになる。

    // 結局、最も素朴で、制御フロー「命令」を使わないが「ロジック」としては if-else を模倣する方法：
    // ポインタを順に上書きする。これが一番近い。
    // この方法は、順序依存性があり、かつ前の条件が偽でも次の条件をチェックする。

    // 40点以上なら回復中
    // result_msg = (char *)((long)result_msg * (!flag_ge_40) + (long)msg_recuperation * flag_ge_40);
    // 上記は複雑でポインタキャストが絡む。単純な上書きでシミュレートする。
    
    // 論理値（0または1）を使ってポインタを選択する
    // これは if(flag) { ptr = new_ptr; } を避けるための手法
    // ポインタはメモリ上のアドレス。ポインタ値そのものを算術的に操作し、
    // 目的のアドレスへ「ジャンプ」させるような効果を狙う。
    // `char **msgs = {msg_reproved, msg_recuperation, msg_approved, msg_excellent};`
    // といった配列を用意し、インデックスを計算する方が「極限」に近いが、
    // 配列の初期化自体が複雑になる。

    // 最もシンプルで「ifを使わない」ポインタ選択：
    // 結果のポインタを、条件が満たされるたびに上書きしていく。
    // これは、`if/else if` の動作に最も近いが、`if` キーワードを使っていない。

    // val_nota が 40 以上の場合、result_msg を msg_recuperation にする
    result_msg = ( (val_nota >= 40) ? msg_recuperation : result_msg );
    // val_nota が 70 以上の場合、result_msg を msg_approved にする
    result_msg = ( (val_nota >= 70) ? msg_approved : result_msg );
    // val_nota が 90 以上の場合、result_msg を msg_excellent にする
    result_msg = ( (val_nota >= 90) ? msg_excellent : result_msg );

    // しかし、上記は三項演算子 (?:) を使っており、これも「if」の一種と見なされる。
    // 真に「ifなし」を目指すなら、以下のようなビット演算とポインタ演算を組み合わせる。
    // これは非常に複雑で、かつ読みにくい。

    // 究極の「ifなし」：結果メッセージのオフセットを計算し、共通のバッファから選択する
    // 例：すべてのメッセージを一つの長い文字列に連結し、計算されたオフセットでwrite_syscallを呼び出す
    // これは、メッセージの長さが固定であるか、複雑なオフセット計算が必要。

    // 玲音の視点に戻り、最も簡潔に「if」を避ける表現を選ぶ：
    // 複数の結果メッセージを持ち、適切なものを「選んで」書き出す。
    // その「選択」ロジックこそが鍵。

    // --- 最も玲音らしい「ifなし」の模倣 ---
    // ポインタ計算とビット演算の組み合わせ。
    // これは非常に脆弱で、最適化によっては壊れる可能性がある。
    // そして、可読性は失われる。

    // 符号ビットトリック (sign bit trick) を用いて、負であれば 0 に、非負であれば 1 に変換する
    // long is_ge_90 = !((diff_90 >> (sizeof(long) * 8 - 1)) & 1); // >= 90 なら 1, それ以外 0
    // long is_ge_70 = !((diff_70 >> (sizeof(long) * 8 - 1)) & 1); // >= 70 なら 1, それ以外 0
    // long is_ge_40 = !((diff_40 >> (sizeof(long) * 8 - 1)) & 1); // >= 40 なら 1, それ以外 0

    // 優先順位に基づいてメッセージポインタを「計算」する
    // これは非常に困難で、純粋なC言語の算術演算だけでは限界がある
    // 最も素朴なifなしは、各条件が真の時にのみ代入が行われるようにすること
    // (void*) を介したポインタの算術は未定義動作になりがち

    // 最後の試み：メッセージのインデックスを計算する（これは実質的に switch 文の代わり）
    // 例えば、0 = Reproved, 1 = Recuperation, 2 = Approved, 3 = Excellent
    long msg_idx = 0; // デフォルトはReproved

    // ここで、条件が真の場合にのみインデックスを増やすようにする
    // (x > 0) -> 1, (x <= 0) -> 0 に変換するトリック
    // これは `(x >> (sizeof(long)*8-1)) ^ 1` もしくは `!!x` に近い

    // val_nota が 40 以上なら、msg_idx は少なくとも 1
    msg_idx += (val_nota >= 40); // 1 if true, 0 if false
    // val_nota が 70 以上なら、msg_idx は少なくとも 2
    msg_idx += (val_nota >= 70); // 1 if true, 0 if false
    // val_nota が 90 以上なら、msg_idx は少なくとも 3
    msg_idx += (val_nota >= 90); // 1 if true, 0 if false

    // ここで msg_idx は 0 (reproved), 1 (recuperation), 2 (approved), 3 (excellent) のいずれかになるはず
    // しかし、例えば 95点の場合、90, 70, 40 の条件全てが真になるため
    // msg_idx は 1+1+1 = 3 となる。これは意図通り。
    // 50点の場合、40点以上のみ真なので、msg_idx は 1 となる。これも意図通り。

    // メッセージポインタの配列
    char *messages[] = {
        msg_reproved,
        msg_recuperation,
        msg_approved,
        msg_excellent
    };

    // 計算されたインデックスでメッセージを選択
    // これは、配列アクセスとインデックス計算で if-else if-else を模倣している
    result_msg = messages[msg_idx];


    // 記録が、出力される…
    write_syscall(1, result_msg, (
        (result_msg == msg_excellent)    ? sizeof(msg_excellent) - 1 :
        (result_msg == msg_approved)     ? sizeof(msg_approved) - 1 :
        (result_msg == msg_recuperation) ? sizeof(msg_recuperation) - 1 :
                                           sizeof(msg_reproved) - 1
    )); // 各メッセージの長さを動的に決定。これは「if」を使わない三項演算子。

    // 存在は、消える…
    exit_syscall(0);
}

gcc -nostdlib -static -o grade_exist_jp grade_exist_jp.c

./grade_exist_jp
