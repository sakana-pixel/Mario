#include"InGameScene.h"
#include"../File/AssetContainer.h"
#include"../File/StageData.h"
#include"../Input/InputManager.h"

#include"../Actor/Character/Mario.h"
#include"../Actor/Character/Enemy/kuribo-.h"
#include"../Actor/Character/Enemy/nokonoko.h"
#include"../Actor/Item/OneUpMushroom.h"
#include"../Actor/Item/FireFlower.h"
#include"../Actor/Item/Mushroom.h"
#include"../Actor/Item/SuperStar.h"

#include <DxLib.h>
#include <fstream>
#include <sstream>

InGameScene::InGameScene()
    :SceneBase()
    ,player(nullptr)
    ,enemy(nullptr)
    ,font_handle(NULL)
    , floor(-1)
    , hatena(nullptr)
    , block(-1)
    , hard_block(-1)
    , dokan_lu(-1)
    , dokan_ru(-1)
    , dokan_ld(-1)
    , dokan_rd(-1)
    , cloud0(-1),cloud1(-1),cloud2(-1),cloud3(-1),cloud4(-1),cloud5(-1)
    , ha0(-1),ha1(-1),ha2(-1)
    , Mt0(-1),Mt1(-1),Mt2(-1),Mt3(-1),Mt4(-1),Mt5(-1)
    , sky(-1)
{

}

InGameScene::~InGameScene()
{
    Finalize();
}

void InGameScene::Initialize()
{
    //画像アセット読み込み
    floor = AssetContainer::Get()->GetImages("floor.png");
    block = AssetContainer::Get()->GetImages("block.png");
    hard_block = AssetContainer::Get()->GetImages("kai_block.png");

    dokan_lu = AssetContainer::Get()->GetImages("dokan_left_up.png");
    dokan_ru = AssetContainer::Get()->GetImages("dokan_right_up.png");
    dokan_ld = AssetContainer::Get()->GetImages("dokan_left_down.png");
    dokan_rd = AssetContainer::Get()->GetImages("dokan_right_down.png");

    hatena = new DivSprite("hatena.png", 4, 1);

    cloud0= AssetContainer::Get()->GetImages("cloud1.png");
    cloud1= AssetContainer::Get()->GetImages("cloud2.png");
    cloud2= AssetContainer::Get()->GetImages("cloud3.png");
    cloud3= AssetContainer::Get()->GetImages("cloud4.png");
    cloud4= AssetContainer::Get()->GetImages("cloud5.png");
    cloud5= AssetContainer::Get()->GetImages("cloud6.png");

    ha0= AssetContainer::Get()->GetImages("ha0.png");
    ha1= AssetContainer::Get()->GetImages("ha1.png");
    ha2= AssetContainer::Get()->GetImages("ha2.png");

    Mt0= AssetContainer::Get()->GetImages("mountain_left.png");
    Mt1= AssetContainer::Get()->GetImages("mountain_right.png");
    Mt2= AssetContainer::Get()->GetImages("mountain_surface.png");
    Mt3= AssetContainer::Get()->GetImages("mountain_surface1.png");
    Mt4= AssetContainer::Get()->GetImages("mountain_surface2.png");
    Mt5= AssetContainer::Get()->GetImages("mountain_up.png");

    sky= AssetContainer::Get()->GetImages("sora.png");

    //ステージデータの初期化とCSV読み込み
    StageData::Get();
    LoadBackgroundData();
    LoadStageData();
}

eSceneType InGameScene::Update(float delta_second)
{
    PlayUpdate(delta_second);
    return eSceneType::eInGame;
}

void InGameScene::Draw() const
{
    //先に背景を描画する
    for (size_t y = 0; y < bg_data.size(); ++y)
    {
        for (size_t x = 0; x < bg_data[y].size();++x)
        {
            const std::string& cell = bg_data[y][x];
            
            //背景描画の座標設定
            int draw_x = static_cast<int>(StageData::STAGE_OFFSET_X + x * StageData::CHIP_SIZE);
            int draw_y = static_cast<int>(StageData::STAGE_OFFSET_Y + y * StageData::CHIP_SIZE);

            if (cell == "z")
            {
                DrawGraph(draw_x, draw_y, cloud0, TRUE);
            }
            else if (cell == "h")
            {
                DrawGraph(draw_x, draw_y, cloud1, TRUE);
            }
            else if (cell == "i")
            {
                DrawGraph(draw_x, draw_y, cloud2, TRUE);
            }
            else if (cell == "j")
            {
                DrawGraph(draw_x, draw_y, cloud3, TRUE);
            }
            else if (cell == "k")
            {
                DrawGraph(draw_x, draw_y, cloud4, TRUE);
            }
            else if (cell == "l")
            {
                DrawGraph(draw_x, draw_y, cloud5, TRUE);
            }
            else if (cell == "x")
            {
                DrawGraph(draw_x, draw_y, ha1, TRUE);
            }
            else if (cell == "a")
            {
                DrawGraph(draw_x, draw_y, ha0, TRUE);
            }
            else if (cell == "b")
            {
                DrawGraph(draw_x, draw_y, ha2, TRUE);
            }
            else if (cell == "y")
            {
                DrawGraph(draw_x, draw_y, Mt2, TRUE);
            }
            else if (cell == "c")
            {
                DrawGraph(draw_x, draw_y, Mt0, TRUE);
            }
            else if (cell == "d")
            {
                DrawGraph(draw_x, draw_y, Mt1, TRUE);
            }
            else if (cell == "e")
            {
                DrawGraph(draw_x, draw_y, Mt5, TRUE);
            }
            else if (cell == "f")
            {
                DrawGraph(draw_x, draw_y, Mt3, TRUE);
            }
            else if (cell == "g")
            {
                DrawGraph(draw_x, draw_y, Mt4, TRUE);
            }
            else if (cell == "0")
            {
                DrawGraph(draw_x, draw_y, sky, TRUE);
            }
        }
    }
    //ステージを描画する
    const auto& stage_map = StageData::Get()->GetAll();
    for (size_t y = 0;y < stage_map.size();++y)
    {
        for (size_t x = 0;x < stage_map[y].size();++x)
        {
			//ステージデータのパネルIDを取得  
            ePanelID id = stage_map[y][x];
            //何もなかったらスキップ
            if (id == ePanelID::eNone)
            {
                continue;
            }

            //ステージ描画の座標設定
            int draw_x = static_cast<int>(StageData::STAGE_OFFSET_X + x * StageData::CHIP_SIZE);
            int draw_y = static_cast<int>(StageData::STAGE_OFFSET_Y + y * StageData::CHIP_SIZE);

            DrawGraph(draw_x, draw_y, floor, TRUE);
        }
    }

    //キャラクターの描画
    for (auto actor : owned_actors)
    {
        if (actor)
        {
            actor->Draw();
        }
    }
}

void InGameScene::Finalize()
{
    //アクタを解放する
    for (auto actor : owned_actors)
    {
        delete actor;
    }
    owned_actors.clear();

    if (hatena)
    {
        delete hatena;
        hatena = nullptr;
    }
}

eSceneType InGameScene::GetNowSceneType() const
{
    return eSceneType::eInGame;
}

void InGameScene::LoadStageData()
{
    //ステージの読み込み
    std::string stage1 = "assets/data/mario_stage_2d_array.csv";
    std::string stage2 = "assets/data/mario_underground_2d_array.csv";
    std::ifstream file(stage1);
    //何もなかったらやり直し
    if (!file.is_open())
    {
        return;
    }

    //CSVの行を1行ずつ読み込む
    std::string line;
    int y = 0;

    while (std::getline(file, line))
    {
        //空行はスキップ
        if (line.empty())
        {
            continue;
        }
        //CSVの行をカンマ分割で処理
        std::stringstream ss(line);
        std::string cell;
        int x = 0;

        //CSVのセルを1つずつ処理
        while (std::getline(ss, cell, ','))
        {
            if (!cell.empty())
            {
                //ステージデータの座標計算
                Vector2 pos(
                    StageData::STAGE_OFFSET_X + x * StageData::CHIP_SIZE,
                    StageData::STAGE_OFFSET_Y + y * StageData::CHIP_SIZE
                );

                if (cell == "1")
                {
                    StageData::Get()->SetPanelData(ePanelID::eWall, pos, 1, 1);
                }
                else if (cell == "2")
                {
                    StageData::Get()->SetPanelData(ePanelID::eWall, pos, 1, 1);
                }
                else if (cell == "3")
                {
                    StageData::Get()->SetPanelData(ePanelID::eWall, pos, 1, 1);
                }
                else if (cell == "4")
                {
                    StageData::Get()->SetPanelData(ePanelID::eWall, pos, 1, 1);
                }
                else if (cell == "a")
                {
                    StageData::Get()->SetPanelData(ePanelID::eWall, pos, 1, 1);
                }
            }
            x++;
        }
        y++;
    }

}

void InGameScene::LoadBackgroundData()
{
    std::string back_stage = "assets/data/mario_clouds_hills_bushes_only.csv";
    std::ifstream file(back_stage);
    //開けなかったらやり直し
    if (!file.is_open())
    {
        return;
    }
    bg_data.clear();
    std::string line;

    while (std::getline(file, line))
    {
        //空行はスキップ
        if (line.empty())
        {
            continue;
        }
        //CSVの行をカンマ分割で処理
        std::stringstream ss(line);
        //CSVのセルを1つずつ処理
        std::string cell;
        //CSVの行を格納するベクター
        std::vector<std::string> row;

        //SCVのセルを１つずつ処理
        while (std::getline(ss, cell, ','))
        {
            //空セルはスキップ
            row.push_back(cell);
        }
        bg_data.push_back(row);
    }
}

void InGameScene::ChangeGameState(eGameState new_state)
{
    state = new_state;
}

void InGameScene::PlayUpdate(float delta_second)
{
    for (auto actor : owned_actors)
    {
        if (actor)
        {
            actor->Update(delta_second);
        }
    }
}

void InGameScene::CheckCollision()
{

}