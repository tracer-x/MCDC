; ModuleID = 'example.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"Hi\00", align 1
@.str1 = private unnamed_addr constant [4 x i8] c"Bye\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 0, i32* %1
  %2 = load i32* %x, align 4
  %3 = icmp sgt i32 %2, 5
  br i1 %3, label %4, label %7

; <label>:4                                       ; preds = %0
  %5 = load i32* %y, align 4
  %6 = icmp slt i32 %5, 20
  br i1 %6, label %16, label %7

; <label>:7                                       ; preds = %4, %0
  %8 = load i32* %a, align 4
  %9 = icmp sgt i32 %8, 20
  br i1 %9, label %16, label %10

; <label>:10                                      ; preds = %7
  %11 = load i32* %b, align 4
  %12 = icmp slt i32 %11, 50
  br i1 %12, label %13, label %18

; <label>:13                                      ; preds = %10
  %14 = load i32* %c, align 4
  %15 = icmp sgt i32 %14, 100
  br i1 %15, label %16, label %18

; <label>:16                                      ; preds = %13, %7, %4
  %17 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0))
  br label %20

; <label>:18                                      ; preds = %13, %10
  %19 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str1, i32 0, i32 0))
  br label %20

; <label>:20                                      ; preds = %18, %16
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.4.2- (branches/release_34) (based on LLVM 3.4.2)"}
