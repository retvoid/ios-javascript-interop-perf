#import "ViewController.h"
#import "JSCoreTest.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    UIView* view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
    view.backgroundColor = UIColor.redColor;
    
    runJSCore();
    
    [self.view addSubview: view];
}


@end
